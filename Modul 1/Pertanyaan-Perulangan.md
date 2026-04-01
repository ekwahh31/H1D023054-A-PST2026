# PERTANYAAN PRAKTIKUM PEMOGRAMAN SISTEM TERTANAM - BAGIAN PERULANGAN

## Pertanyaan
1.6.4 Pertanyaan Praktikum
1. Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan!
2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!
3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!
4. Buatkan program agar LED menyala tiga LED kanan dan tiga LED kiri secara bergantian

## Jawaban
1. Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan!
<img width="1034" height="790" alt="image" src="https://github.com/user-attachments/assets/baedf4cf-0786-4fb0-9e18-a637ed1ce25b" />

Link ThinkerCad : https://www.tinkercad.com/things/8JxYdBKRbuL-modul-1-praktikum?sharecode=zq8Julge3hNoT7e3VZYYTJBHpdxZWI1mN5UKa5Egh4k

2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!
```cpp
for (int ledPin = 2; ledPin < 8; ledPin++) {
   // hidupkan LED pin nya:
   digitalWrite(ledPin, HIGH);
   delay(timer);
   // matikan pin LED nya:
   digitalWrite(ledPin, LOW);
  }
```
Perulangan tersebut menghidupkan led yang ada dari pin 2 sampai ke pin 7. Jika posisi led yang ada di pin dua berada disebelah kiri, maka led akan menyala dari kiri ke kanan, begitupun dengan sebaliknya.

3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!
```cpp
for (int ledPin = 7; ledPin >= 2; ledPin--) {
    // menghidupkan pin:
    digitalWrite(ledPin, HIGH);
    delay(timer);
    // mematikan pin:
    digitalWrite(ledPin, LOW);
  }
```
Perulangan tersebut menghidupkan led yang ada dari pin 7 hingga ke pin 2. Jika posisi pin 7 berada di paling kanan, maka lampu led akan bergerak dari kanan ke kiri.

4. Buatkan program agar LED menyala tiga LED kanan dan tiga LED kiri secara bergantian
```cpp
void setup(){
  for(int i = 2; i <= 7; i++){
    pinMode(i, OUTPUT);
  }
}

void loop(){
  // program menyalakan lampu pada 3 lampu kiri, pin 2,3, dan 4, serta mematikan lampu dengan pin 5,6, dan 7
   digitalWrite(7,HIGH);
   digitalWrite(6,HIGH);
   digitalWrite(5,HIGH);
   digitalWrite(4,LOW);
   digitalWrite(3,LOW);
   digitalWrite(2,LOW);
    delay(1000);

  // program menayalakan lampu pada 3 lampu kanan, pin 5,6, dan 7, serta mematikan lampu dengan pin 2,3, dan 4
    digitalWrite(7,LOW);
    digitalWrite(6,LOW);
    digitalWrite(5,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(3,HIGH);
    digitalWrite(2,HIGH);
    delay(1000);
}
```
