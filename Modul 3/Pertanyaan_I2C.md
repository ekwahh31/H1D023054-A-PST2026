# PERTANYAAN PRAKTIKUM PEMOGRAMAN SISTEM TERTANAM - Inter-Integrated_Circuit (I2C)

## Pertanyaan
1. Jelaskan bagaimana cara kerja komunikasi I2C antara Arduino dan LCD pada rangkaian tersebut!

2. Apakah pin potensiometer harus seperti itu? Jelaskan yang terjadi apabila pin kiri dan pin kanan tertukar!

3. Modifikasi program dengan menggabungkan antara UART dan I2C (keduanya sebagai output) sehingga:
- Data tidak hanya ditampilkan di LCD tetapi juga di Serial Monitor
- Adapun data yang ditampilkan pada Serial Monitor sesuai dengan table berikut:

| ADC: 0 | Volt: 0.00V | Persen: 0% |
| :--- | :--- | :--- |

Tampilan jika potensiometer dalam kondisi diputar paling kiri
- ADC: 0 0% | setCursor(0, 0) dan Bar (level) | setCursor(0, 1)
- Berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

4) Lengkapi table berikut berdasarkan pengamatan pada Serial Monitor

| ADC | Volt (V)| Persen (%) |
| --- | --- | --- |
| 1 |||
| 21|||
| 49 |||
| 74 |||
| 96 |||

## Jawaban
1. I2C adalah protokol komunikasi yang menggunakan 2 kabel: SDA (Serial Data) dan SCL (Serial Clock) untuk mengirim data. Arduino menghubungkan kedua kabel ini ke pin A4 (SDA) dan A5 (SCL). Ketika program berjalan, Arduino mengirim alamat I2C (0x27) ke bus untuk menemukan LCD module. Setelah terhubung, Arduino mengirim perintah seperti setCursor dan print melalui kabel SDA, sementara kabel SCL memberikan sinyal clock untuk sinkronisasi. Dengan cara ini, Arduino bisa mengontrol LCD hanya menggunakan 2 kabel saja tanpa perlu banyak kabel tambahan.

2. Tidak harus, Karena posisi kiri GND dan kanan VCC hanya menentukan arah perubahan nilai. Jika pin kiri dan kanan ditukar, potensiometer tetap bekerja normal, tetapi arah pembacaan ADC akan terbalik. Saat diputar ke arah yang sebelumnya menaikkan nilai, sekarang justru menurunkan nilai, karena tegangan yang masuk ke pin tengah berubah arah dari tinggi ke rendah atau sebaliknya.

3. Modifikas Kode
```cpp
  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>
  
  // Inisialisasi LCD I2C alamat 0x27 ukuran 16x2
  LiquidCrystal_I2C lcd(0x27, 16, 2);
  
  const int pinPot = A0;
  
  void setup() {
    Serial.begin(9600);   // Inisialisasi komunikasi UART
    lcd.init();           // Inisialisasi LCD
    lcd.backlight();      // Nyalakan backlight
  }
  
  void loop() {
    int nilai = analogRead(pinPot); // Baca ADC 0-1023
  
    float volt = nilai * (5.0 / 1023.0); // Konversi ke volt
    int persen = map(nilai, 0, 1023, 0, 100); // Konversi ke persen
    int panjangBar = map(nilai, 0, 1023, 0, 16); // Untuk bar LCD
  
    // Output ke Serial Monitor
    Serial.print("ADC: ");
    Serial.print(nilai);
    Serial.print(" | Volt: ");
    Serial.print(volt, 2);
    Serial.print("V | Persen: ");
    Serial.print(persen);
    Serial.println("%");
  
    // Baris 1 LCD
    lcd.setCursor(0, 0);
    lcd.print("ADC:");
    lcd.print(nilai);
    lcd.print(" ");
    lcd.print(persen);
    lcd.print("%   "); // clear sisa
  
    // Baris 2 LCD (bar)
    lcd.setCursor(0, 1);
    for (int i = 0; i < 16; i++) {
      if (i < panjangBar) {
        lcd.print((char)255);
      } else {
        lcd.print(" ");
      }
    }
  
    delay(200);
  }
```

4. Lengkapi Tabel

| ADC | Volt (V)| Persen (%) |
| --- | --- | --- |
| 1 | 0.00V | 0% |
| 21 | 0.10V | 1% |
| 49 | 0.20V | 4% |
| 74 | 0.36V | 7% |
| 96 | 0.47V | 9% |

## Dokumentasi
THinkercad : https://www.tinkercad.com/things/k2gJDnTEBPQ-i2c

<img width="1905" height="746" alt="image" src="https://github.com/user-attachments/assets/c65cf193-2927-46c3-b60f-f43f52c2cb41" />
