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
const int ledPin = 12;                     // Mendefinisikan pin 12 sebagai output untuk LED
int timeDelay = 1000;                      // Inisialisasi delay 1000ms (1 detik) sebagai nilai awal
bool isReverse = false;                    // Untuk mengontrol percepatan/perlambatan

void setup() {                             
  pinMode(ledPin, OUTPUT);                 // Set pin 12 sebagai mode OUTPUT
}

void loop() {                              
  // Nyalakan LED
  digitalWrite(ledPin, HIGH);              // Set pin 12 HIGH atau menyalakan LED
  delay(timeDelay);                        // Tahan LED menyala selama timeDelay milidetik
  
  // Matikan LED
  digitalWrite(ledPin, LOW);               // Set pin 12 LOW atau mematikan LED
  delay(timeDelay);                        // Tahan LED mati selama timeDelay milidetik
  
  if (timeDelay <= 100) {                  // Jika timeDelay sudah mencapai 100ms atau lebih kecil
    isReverse = true;                      // Aktifkan isReverse untuk mulai perlambatan
  } else if (timeDelay >= 1000) {          // Jika timeDelay kembali ke 1000ms atau lebih
    isReverse = false;                     // Nonaktifkan isReverse untuk di percepatan lagi
    delay(3000);                           // Tahan selama 3 detik sebelum siklus berikutnya
    timeDelay = 1000;                      // Reset timeDelay ke nilai awal (1000ms)
  }
  
  if (isReverse == false) {                // Jika isReverse tidak aktif (percepatan)
    timeDelay -= 100;                      // Kurangi timeDelay 100ms setiap siklus (mempercepat)
  } else {                                 // Jika isReverse aktif (perlambatan)
    timeDelay += 100;                      // Tambah timeDelay 100ms setiap siklus (memperlambat)
  }
}
```
