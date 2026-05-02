# PERTANYAAN PRAKTIKUM PEMOGRAMAN SISTEM TERTANAM - Pulse Width Modulation (PWM)

## Pertanyaan
1. Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi analogWrite()!
2. Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?
3. Modifikasilah program berikut agar LED hanya menyala pada rentang kecerahan sedang, yaitu hanya ketika nilai PWM berada pada rentang 50 sampai 200. Jelaskan program pada file README.md.

## Jawaban
1. Fungsi analogWrite() menggunakan teknik PWM (Pulse Width Modulation) yang menghidupkan dan mematikan LED dengan sangat cepat. Semakin tinggi nilai yang diberikan (0-255), semakin lama LED menyala dibanding mati, sehingga mata kita melihatnya lebih terang. Sebaliknya, semakin rendah nilainya, semakin lama LED mati dibanding menyala, sehingga terlihat lebih redup. Dengan cara ini, kecerahan LED dapat diatur secara halus tanpa mengubah tegangan yang diberikan.

2. ADC memiliki rentang 0-1023 karena menggunakan 10 bit resolusi, sementara PWM memiliki rentang 0-255 karena menggunakan 8 bit resolusi. Fungsi map() dalam program berfungsi untuk mengkonversi nilai ADC yang lebih besar ke nilai PWM yang lebih kecil dengan membuat perbandingan linear antara kedua rentang tersebut. Dengan cara ini, setiap gerakan potensiometer dapat mengubah kecerahan LED secara proporsional.

3. Modifikasi Kode
```cpp
    // ===================== PEMROSESAN DATA (SCALING) =====================
    pwm = map(nilaiADC,
            0,     // ADC minimum
            1023,  // ADC maksimum
            50,    // PWM minimum (diubah dari 0)
            200);  // PWM maksimum (diubah dari 255)
``` 
Perubahan dilakukan pada fungsi map() dengan mengubah parameter nilai PWM dari rentang 0 hingga 255 menjadi 50 hingga 200. Hal ini membuat LED hanya menyala dalam rentang kecerahan sedang, sehingga meskipun potensiometer diputar dari ujung ke ujung, nilai PWM yang dihasilkan tetap terbatas antara 50-200. Dengan cara ini, LED tidak akan pernah benar-benar mati (PWM 0) atau terlalu terang (PWM 255), melainkan selalu menyala dalam tingkat kecerahan sedang yang stabil.