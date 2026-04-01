# PERTANYAAN PRAKTIKUM PEMOGRAMAN SISTEM TERTANAM - BAGIAN PERCABANGAN

## Pertanyaan
1.5.4 Pertanyaan Praktikum:
1. Pada kondisi apa program masuk ke blok if?
2. Pada kondisi apa program masuk ke blok else?
3. Apa fungsi dari perintah delay(timeDelay)?
4. Jika program yang dibuat memiliki alur mati → lambat → cepat → reset (mati), ubah menjadi LED tidak langsung reset → tetapi berubah dari cepat → sedang → mati 

## Jawaban
1. Pada kondisi apa program masuk ke blok if?
```
  if (timeDelay <= 100)
```
Program akan masuk ke blok if ketika nilai `timeDelay` sudah mencapai lebih kecil atau sama dengan 100 milidetik.

2. Pada kondisi apa program masuk ke blok else?
```
else { 
    timeDelay -= 100;   // percepatan bertahap 
  } 
```
Program kan masuk ke blok else ketika nilai `timeDelay` lebih besar dari 100 milidetik. Maka program akan mempercepat kedipan LED dengan mengurangi nilai `timeDelay` sebesar 100 milidetik setiap siklus perulangannya.

3. Apa fungsi dari perintah delay(timeDelay)?
```
delay(timeDelay);
```
Perintah tersebut memiliki fungsi untuk menunda atau delay pada eksekusi kode selanjutnya sebanyak isi dari variabel `timeDelay`.

4. Jika program yang dibuat memiliki alur mati → lambat → cepat → reset (mati), ubah menjadi LED tidak langsung reset → tetapi berubah dari cepat → sedang → mati

```
const int ledPin = 12;
int timeDelay = 1000;
bool isReverse = false;                   //indikator apakah urutan akan mempercepat atau memperlambat

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {  
  // Nyalakan LED
  digitalWrite(ledPin, HIGH);
  delay(timeDelay);  
  // Matikan LED
  digitalWrite(ledPin, LOW);
  delay(timeDelay);  
  
  if (timeDelay <= 100) {
    isReverse = true;                      // aktif ketika timeDelay menyentuh angka 100 atau lebih kecil
  } else if (timeDelay >= 1000) {
    isReverse = false;                     //reset indikator isReverse
    delay(3000);                           //jeda sebelum reset
    timeDelay = 1000;                      //reset waktu delay
  }
  
  if (isReverse == false) {
    timeDelay -= 100;                      // percepatan berkala ketika isReverse tidak aktif
  } else {
    timeDelay += 100;                      //perlambatan berkala ketika isReverse aktif
  }
} 
```
