# PERTANYAAN PRAKTIKUM PEMOGRAMAN SISTEM TERTANAM - UART

## Pertanyaan
1. Jelaskan proses dari input keyboard hingga LED menyala/mati!
2. Mengapa digunakan Serial.available() sebelum membaca data? Apa yang terjadi jika baris tersebut dihilangkan?
3. Modifikasi program agar LED berkedip (blink) ketika menerima input '2' dengan kondisi jika ‘2’ aktif maka LED akan terus berkedip sampai perintah selanjutnya diberikan dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!
4. Tentukan apakah menggunakan delay() atau milis()! Jelaskan pengaruhnya terhadap sistem

## Jawaban
1. Ketika pengguna mengetik karakter di keyboard, data tersimpan di serial buffer. Arduino secara terus-menerus mengecek buffer dengan `Serial.available()`. Ketika ada data, `Serial.read()` membaca satu karakter ke variabel `data`. Kemudian program membandingkan karakter tersebut: jika '1', maka `digitalWrite(PIN_LED, HIGH)` akan menyalakan LED dengan mengirim tegangan HIGH ke PIN 13; jika '0', maka `digitalWrite(PIN_LED, LOW)` akan mematikan LED dengan mengirim tegangan LOW. Setelah itu, Serial.println() mengirim pesan status kembali ke komputer sebagai feedback.

2. `Serial.available()` digunakan untuk mengecek apakah ada data di buffer sebelum membacanya. Fungsi ini mencegah program mencoba membaca data yang belum ada, sehingga Arduino tetap responsif dan tidak hang/freeze. Jika baris tersebut dihilangkan, program akan selalu mencoba membaca buffer meskipun kosong. Ketika buffer kosong, `Serial.read()` mengembalikan nilai -1, yang tidak akan match dengan '1' atau '0'. Akibatnya, program menjadi tidak responsif dan tidak dapat menjalankan perintah lain dengan lancar, karena microcontroller akan terus menunggu data input.

3. Modifikasi program agar LED berkedip ketika menerima input '2' 
```cpp
    #include <Arduino.h>

    const int PIN_LED = 13;
    // Variabel baru untuk menyimpan status blink
    bool isBlinking = false;          // Flag untuk menentukan LED sedang berkedip atau tidak
    unsigned long lastBlinkTime = 0;  // Menyimpan waktu terakhir LED berubah status
    const int BLINK_INTERVAL = 500;   // Interval berkedip 500ms (ON 500ms, OFF 500ms)

    void setup() {
    Serial.begin(9600);
    Serial.println("Ketik '1' untuk menyalakan LED, '0' untuk mematikan LED, '2' untuk berkedip");
    pinMode(PIN_LED, OUTPUT);
    }

    void loop() {
    // Jika LED sedang berkedip, jalankan logika blink
    if (isBlinking) {                           // Cek apakah mode blink aktif
        unsigned long currentTime = millis();     // Ambil waktu saat ini (dalam milidetik)
        
        // Jika interval sudah tercapai, toggle pin LED
        if (currentTime - lastBlinkTime >= BLINK_INTERVAL) {  // Jika selisih waktu >= 500ms
        digitalWrite(PIN_LED, !digitalRead(PIN_LED));       // Toggle LED (HIGH jadi LOW atau sebaliknya)
        lastBlinkTime = currentTime;                         // Update waktu terakhir
        }
    }
    
    // Cek apakah ada data dari serial
    if (Serial.available() > 0) {       // Cek apakah ada data dari komputer
        char data = Serial.read();        // Baca 1 karakter

        if (data == '1') {
        isBlinking = false;             // Hentikan mode blink
        digitalWrite(PIN_LED, HIGH);    // Nyalakan LED
        Serial.println("LED ON");
        }
        else if (data == '0') {
        isBlinking = false;             // Hentikan mode blink
        digitalWrite(PIN_LED, LOW);     // Matikan LED
        Serial.println("LED OFF");
        }
        else if (data == '2') {           // Input baru untuk mode blink
        isBlinking = true;              // Aktifkan mode blink
        lastBlinkTime = millis();       // Set waktu awal untuk blink
        Serial.println("LED BLINK AKTIF - Ketik 1 atau 0 untuk menghentikan");
        }
        else if (data != '\n' && data != '\r') {
        // Hanya muncul jika bukan 1, 0, 2, atau ENTER
        Serial.println("Perintah tidak dikenal");
        }
    }
    }
```

4. `delay()` membuat program berhenti total, jadi serial monitor tidak bisa menerima perintah baru sampai delay selesai. Pengguna harus menunggu lama untuk memberikan input berikutnya. Sebaliknya, `millis()` tidak menghentikan program—loop terus berjalan, sehingga serial monitor selalu siap menerima perintah kapan saja. User bisa menghentikan blink dengan mengetik '0' atau '1' langsung tanpa menunggu. `millis()` juga lebih hemat daya dan memungkinkan program melakukan dua hal sekaligus: memproses blink dan mengecek serial input. Jadi untuk sistem tertanam, `millis()` adalah pilihan yang lebih baik.