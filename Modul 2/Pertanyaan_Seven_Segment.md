# PERTANYAAN PRAKTIKUM PEMOGRAMAN SISTEM TERTANAM - BAGIAN SEVENT SEGMENT

## Pertanyaan
2.5.4 Pertanyaan Praktikum
1. Gambarkan rangkaian schematic yang digunakan pada percobaan!
2. Apa yang terjadi jika nilai num lebih dari 15?
3. Apakah program ini menggunakan common cathode atau common anode? Jelaskan alasanya!
4. Modifikasi program agar tampilan berjalan dari F ke 0 dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

## Jawaban
1. Gambarkan rangkaian schematic yang digunakan pada percobaan!
<img width="1009" height="777" alt="image" src="https://github.com/user-attachments/assets/f9034c5f-bafb-4030-9352-a406f2cbe5dc" />

2. Apa yang terjadi jika nilai num lebih dari 15?
```
digitPattern[16][8]
```
   Karena array hanya didefinisikan untuk indeks 0-15 maka jika nilai num lebih dari 15 maka akan terjadi eror/crash karena program mencari data yang tidak ada.

4. Apakah program ini menggunakan common cathode atau common anode? Jelaskan alasanya!

Program ini menggunakan common anode karena ada operator inversi (!) di fungsi `displayDigit`. Ketika pola `digitPattern` bernilai 1 (segment harus nyala), inversi mengubahnya menjadi 0 (LOW) sebelum dikirim ke pin. Pada common anode, semua segment + terhubung ke power dan segment nyala ketika mendapat sinyal LOW. Ini berbeda dengan common cathode yang nyala dengan sinyal HIGH tanpa perlu inversi.

5. Modifikasi program agar tampilan berjalan dari F ke 0 dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!
```
void loop()
{
  // Inisialisasi loop dari nilai 15 (F) turun ke 0 dengan decrement (i--)
  for(int i=15;i>=0;i--)
  {
    // Panggil fungsi displayDigit() untuk menampilkan digit sesuai nilai i
    displayDigit(i);
    // Delay 1000 ms (1 detik) sebelum menampilkan digit berikutnya
    delay(1000);
  }
}
```
