# DynamicTensorDemo

Bu proje, **mikrodenetleyiciler ve RAM kısıtlı cihazlar için TinyML uygulamaları** için geliştirilmiş bir dinamik tensor yapısı ve quantization demo’sudur. Kod, **Dev-C++** üzerinde geliştirilmiş ve test edilmiştir.

---

## 🔹 Özellikler

- **Dinamik Tensor Yapısı**: 2D matris boyutunda tensor oluşturma ve yönetme  
- **Veri Tipleri**: 32-bit Float (FP32), 16-bit Float (simülasyon) ve 8-bit Integer (INT8)  
- **Union Kullanımı**: Aynı bellek alanını farklı tiplerde okuma ve yazma  
- **Quantization / Dequantization**: Float → INT8 ve geri dönüş  
- **Matrix Multiplication**: Basit 2D matris çarpımı demo  
- **Bellek Analizi**: Tensor türüne göre kullanılan RAM miktarını gösterme  
- **Debugger Mantığı**: Tensor elemanları, quantization ve union değerleri adım adım izlenebilir  
- **Agentic Kodlama**: Kod, duruma göre akıllıca karar vererek işlemleri yönetir  

---

## 🔹 Agentic Kodlama Mantığı

Bu proje, **Agentic Kodlama** yaklaşımıyla tasarlanmıştır; yani kod duruma göre akıllıca davranır:  

- Tensor tipi **FLOAT32, FLOAT16 veya INT8** olduğunda işlemler otomatik olarak uygun şekilde yapılır.  
- **Quantization / Dequantization** sırasında tensor elemanları, bellek ve ölçekleme durumuna göre uyarlanır.  
- **Matrix Multiplication** ve diğer tensor işlemleri, veri tipine göre otomatik dönüşüm ve hesaplama uygular.  
- **Union kullanımı**, aynı bellek alanını farklı tiplerde okuma/yazma ile duruma göre yönetim sağlar.  
- **Memory Usage** fonksiyonu, tensor boyutu ve tipi baz alınarak bellek kullanımını otomatik raporlar.  

Kod, sabit kurallara bağlı kalmaz; duruma göre esnek ve optimize çalışır. İşte bu Agentic Kodlama’nın özü.  

---

## 📦 Kurulum ve Çalıştırma (Dev-C++)

1. **Dev-C++’ta yeni proje oluştur:**  
   - File → New → Project → Console Application → C Project  
   - Projeye isim ver: `TinyML_TensorEngine`  

2. **`main.c` dosyasını projeye ekle:**  
   - File → Add to Project → `main.c`  

3. **Derle ve çalıştır:**  
   - Compile → Build → Run  
   - Konsolda program çıktısı görünecektir.

---

## 📝 Kullanım Örnekleri

- **Tensor Oluşturma**

```c
Tensor A = createTensor(2, 2, FLOAT32);

## 🔹 Örnek Kod Kullanımları

### Quantization
```c
for(int i = 0; i < 4; i++)
    q[i] = quantize(f[i], B.scale, B.zero_point);



