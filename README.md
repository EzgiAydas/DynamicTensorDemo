# Dynamic Tensor Engine
Low-Level Tensor, Quantization & Memory Management in C

Minimal bir C projesi ile Tensor mantığını, Quantization sürecini ve düşük seviyeli bellek yönetimini anlamaya yönelik geliştirilmiş modüler bir sistem.

## Proje Özeti

Bu proje, C dili kullanılarak geliştirilmiş basit fakat mimari olarak anlamlı bir Tensor Motorudur.

Sistem aşağıdaki özellikleri destekler:

✅ FLOAT32, FLOAT16, INT8 veri tipleri

✅ Dinamik bellek yönetimi

✅ Quantization (Nicemleme)

✅ Dequantization

✅ 2D Matris Çarpımı

✅ Bellek kullanım analizi

✅ Union ile ham bellek gösterimi

✅ Debugger ile indeks doğrulama

Amaç, yapay zeka kütüphanelerinin temelinde bulunan veri yönetim mantığını düşük seviyede kavramaktır.

## Sistem Mimarisi (Agentic Yaklaşım)

Bu proje agentic (ajan temelli) kodlama prensibiyle tasarlanmıştır.

Her modülün ayrı bir sorumluluğu vardır:

| Modül            | Görevi                     |
|------------------|----------------------------|
| createTensor()   | Dinamik veri tahsisi       |
| memoryUsage()    | Bellek hesaplama           |
| quantize()       | Float → INT8 dönüşüm       |
| dequantize()     | INT8 → Float dönüşüm       |
| matmul()         | Matris çarpımı             |
| printTensor()    | Tip bağımlı çıktı          |

Bu yapı sayesinde sistem:

Veri tipine göre davranış değiştirir

Aynı fonksiyon farklı tipleri yönetebilir

Modüler ve genişletilebilir bir yapı sunar

Bu yaklaşım, büyük AI framework’lerinin temel mantığına benzer.

## Tensor Veri Yapısı

``` typedef struct {
    void* data;
    DataType type;
    int rows;
    int cols;
    float scale;
    int zero_point;
} Tensor;

```

Bu yapı:

Veriyi (data)

Veri tipini (type)

Boyut bilgisini (rows, cols)

Quantization parametrelerini (scale, zero_point)

tek bir nesnede birleştirir.

Bu sayede Tensor hem matematiksel hem donanımsal bilgiyi taşır.

## Quantization Nedir?

Quantization, yüksek hassasiyetli veriyi daha düşük bitli formata dönüştürme işlemidir.

Amaç:

Bellek tasarrufu

Daha hızlı işlem

Edge cihaz uyumluluğu

Kullanılan Formül:
```
 q = (float_value / scale) + zero_point
```




Ters işlem:

```
float_value = (q - zero_point) * scale
```



Bu projede:

FLOAT32 → INT8 dönüşümü yapılır

INT8 tekrar FLOAT’a çevrilerek doğruluk kontrol edilir

### Sonuç: Bellek kullanımı 4 kat azalır.

## Debugger ile Matris Yönetimi

Matrix çarpımı 3 katmanlı döngü ile gerçekleştirilir:

```
for i
   for j
      for k
         sum += A[i][k] * X[k][j]
```



Debugger kullanılarak:

İndeks hesabı (i*cols + k)

Bellek adresi

Veri tipi dönüşümü

Dequantize edilen değer

adım adım kontrol edilmiştir.

Bu süreç özellikle:

Yanlış indeks erişimini

Taşma hatalarını

Yanlış tip okuma problemlerini

önlemek için kritiktir.

## Union ile Bellek Analizi
```

typedef union {
    float f32;
    uint16_t f16;
    int8_t i8;
    uint32_t raw;
} Value;
```


Union sayesinde:

Aynı bellek alanı farklı tiplerde okunabilir.

Float değerin IEEE-754 karşılığı gözlemlenebilir.

Ham hex çıktısı alınabilir.

Bu teknik:

Donanım seviyesinde analiz

Bit manipülasyonu

Tip dönüşümü

için kullanılır.

## Bellek Kullanım Karşılaştırması
| Veri Tipi | Byte |
|-----------|------|
| FLOAT32   | 4    |
| FLOAT16   | 2    |
| INT8      | 1    |


memoryUsage() fonksiyonu ile her tensor için dinamik hesaplama yapılır.

Bu sayede quantization sonrası kazanım net şekilde görülür.

## Matrix Multiplication (2D Demo)

FLOAT32 tensorlar doğrudan çarpılır.

INT8 tensorlar önce dequantize edilir.

Sonuç FLOAT32 olarak saklanır.

Bu yapı, mixed precision mantığını simüle eder.

## Kullanılan Teknolojiler

 Dil: C

 IDE: Dev C++

 Debugger: Dev C++ built-in debugger

## Kütüphaneler:

stdio.h

stdlib.h

stdint.h

## Projenin Amacı

Bu proje:

Tensor mantığını,

Quantization sistemini,

Bellek optimizasyonunu,

Düşük seviyeli tip dönüşümünü,

Matris indeksleme mantığını,

gerçek bir sistem simülasyonu üzerinden öğretmeyi amaçlar.
