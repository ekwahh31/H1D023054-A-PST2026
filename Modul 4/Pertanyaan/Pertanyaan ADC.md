# PERTANYAAN PRAKTIKUM PEMOGRAMAN SISTEM TERTANAM - Analog to Digital Converter (ADC)

## Pertanyaan
1. Apa fungsi perintah analogRead() pada rangkaian praktikum ini?
2. Mengapa diperlukan fungsi map() dalam program tersebut?
3. Modifikasi program berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap memiliki rentang ADC 0–1023. Jelaskan program pada file README.md

## Jawaban
1. Fungsi dari `analogRead()` adalah untuk membaca nilai dari potensiometer dengan mengubah sinyal analog (tegangan) menjadi angka digital antara 0 hingga 1023.

2. Fungsi dari `map()` adalah untuk mengubah nilai pembacaan ADC (0-1023) menjadi sudut servo (0-180°). Fungsi ini diperlukan karena ADC memberikan nilai 0-1023 tetapi servo hanya mengerti perintah sudut 0-180°.

3. Modifikasi Kode
```cpp
    // ===================== KONVERSI DATA =====================
    pos = map(val,
            0,     // nilai minimum ADC
            1023,  // nilai maksimum ADC
            30,    // sudut minimum servo (diubah dari 0)
            150);  // sudut maksimum servo (diubah dari 180)
```
Perubahan dilakukan pada fungsi map() dengan mengubah parameter sudut servo dari rentang 0° hingga 180° menjadi 30° hingga 150°. Hal ini dilakukan agar servo hanya bergerak dalam batas aman 30°-150° meskipun potensiometer masih memiliki jangkauan ADC penuh dari 0 hingga 1023.