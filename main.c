#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* ===== DATA TYPE ENUM ===== */
typedef enum { FLOAT32, FLOAT16, INT8 } DataType;

/* ===== UNION ===== */
/* Ayný belleði farklý tipte okumak için */
typedef union {
    float f32;
    uint16_t f16;
    int8_t i8;
    uint32_t raw;
} Value;

/* ===== TENSOR STRUCT ===== */
typedef struct {
    void* data;
    DataType type;
    int rows;
    int cols;
    float scale;
    int zero_point;
} Tensor;

/* ===== CREATE TENSOR ===== */
Tensor createTensor(int rows, int cols, DataType type) {
    Tensor t;
    t.rows = rows;
    t.cols = cols;
    t.type = type;
    t.scale = 0.1f;
    t.zero_point = 0;

    int size = rows * cols;

    if (type == FLOAT32)
        t.data = malloc(size * sizeof(float));
    else if (type == FLOAT16)
        t.data = malloc(size * sizeof(uint16_t));
    else
        t.data = malloc(size * sizeof(int8_t));

    return t;
}

/* ===== MEMORY USAGE ===== */
size_t memoryUsage(Tensor* t) {
    size_t element_size;
    if (t->type == FLOAT32) element_size = 4;
    else if (t->type == FLOAT16) element_size = 2;
    else element_size = 1;

    return t->rows * t->cols * element_size;
}

/* ===== QUANTIZATION ===== */
int8_t quantize(float v, float s, int z) {
    return (int8_t)(v / s + z);
}

float dequantize(int8_t v, float s, int z) {
    return (v - z) * s;
}

/* ===== PRINT TENSOR ===== */
void printTensor(Tensor* t) {
    int size = t->rows * t->cols;

    for(int i = 0; i < size; i++) {
        if(t->type == FLOAT32)
            printf("%.2f ", ((float*)t->data)[i]);

        else if(t->type == FLOAT16)
            printf("%u ", ((uint16_t*)t->data)[i]);

        else
            printf("%.2f ",
                   dequantize(((int8_t*)t->data)[i],
                              t->scale, t->zero_point));
    }
    printf("\n");
}

/* ===== SIMPLE MATRIX MULTIPLICATION ===== */
/* Y = A * X  (2D demo) */
void matmul(Tensor* A, Tensor* X, Tensor* Y) {

    for(int i = 0; i < A->rows; i++) {
        for(int j = 0; j < X->cols; j++) {

            float sum = 0;

            for(int k = 0; k < A->cols; k++) {

                float a_val, x_val;

                if(A->type == FLOAT32)
                    a_val = ((float*)A->data)[i*A->cols + k];
                else
                    a_val = dequantize(((int8_t*)A->data)[i*A->cols + k],
                                       A->scale, A->zero_point);

                if(X->type == FLOAT32)
                    x_val = ((float*)X->data)[k*X->cols + j];
                else
                    x_val = dequantize(((int8_t*)X->data)[k*X->cols + j],
                                       X->scale, X->zero_point);

                sum += a_val * x_val;
            }

            ((float*)Y->data)[i*Y->cols + j] = sum;
        }
    }
}

/* ===== MAIN ===== */
int main() {

    printf("Dynamic Tensor Engine\n");

    /* FLOAT32 Tensor */
    Tensor A = createTensor(2, 2, FLOAT32);
    float* f = (float*)A.data;

    f[0]=1.0f; f[1]=2.0f;
    f[2]=3.0f; f[3]=4.0f;

    /* INT8 Tensor */
    Tensor B = createTensor(2, 2, INT8);
    int8_t* q = (int8_t*)B.data;

    for(int i=0;i<4;i++)
        q[i] = quantize(f[i], B.scale, B.zero_point);

    printf("\nFLOAT32 Tensor:\n");
    printTensor(&A);

    printf("\nINT8 Tensor (Dequantized):\n");
    printTensor(&B);

    printf("\nMemory Usage:\n");
    printf("FLOAT32: %zu bytes\n", memoryUsage(&A));
    printf("FLOAT16: %zu bytes\n", memoryUsage(&(Tensor){NULL,FLOAT16,2,2,0,0}));
    printf("INT8: %zu bytes\n", memoryUsage(&B));

    /* Matrix multiplication demo */
    Tensor Y = createTensor(2,2,FLOAT32);
    matmul(&A,&A,&Y);

    printf("\nMatrix Multiplication Result:\n");
    printTensor(&Y);

    /* UNION Demo */
    Value u;
    u.f32 = 0.75f;
    printf("\nUnion Demo:\n");
    printf("Float: %f\n", u.f32);
    printf("Raw Hex: 0x%X\n", u.raw);

    free(A.data);
    free(B.data);
    free(Y.data);

    return 0;
}


