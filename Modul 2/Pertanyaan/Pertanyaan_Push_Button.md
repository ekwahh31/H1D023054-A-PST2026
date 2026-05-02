# PERTANYAAN PRAKTIKUM PEMOGRAMAN SISTEM TERTANAM - BAGIAN COUNTER PUSH BUTTON

## Pertanyaan
2.6.4 Pertanyaan Praktikum
1. Gambarkan rangkaian schematic yang digunakan pada percobaan!
2. Mengapa pada push button digunakan mode INPUT_PULLUP pada Arduino Uno? Apa keuntungannya dibandingkan rangkaian biasa?
3. Jika salah satu LED segmen tidak menyala, apa saja kemungkinan penyebabnya dari sisi hardware maupun software?
4. Modifikasi rangkaian dan program dengan dua push button yang berfungsi sebagai penambahan (increment) dan pengurangan (decrement) pada sistem counter dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

## Jawaban
1. Gambarkan rangkaian schematic yang digunakan pada percobaan!
   <img width="921" height="713" alt="image" src="https://github.com/user-attachments/assets/c5c5311b-5c12-4527-b5c6-bd61b2f1bb90" />

2. Mengapa pada push button digunakan mode INPUT_PULLUP pada Arduino Uno? Apa keuntungannya dibandingkan rangkaian biasa?
   ```cpp
    pinMode(btnUp, INPUT_PULLUP);  // Mengaktifkan pull-up internal

    // Edge detection: dari HIGH ke LOW (tombol ditekan)
    if(lastUpState == HIGH && upState == LOW) {
        currentDigit++;  // Increment counter
    }
   ```
   Arduino Uno memiliki resistor internal yang bisa diaktifkan dengan `INPUT_PULLUP`. Resistor ini membuat pin selalu dalam kondisi HIGH (5V) ketika tombol tidak ditekan. Ketika tombol ditekan, pin terhubung ke GND dan menjadi LOW (0V). keuntungannya adalah membuat rangkaian menjadi sederhana karena tidak perlu menambahkan resistor external pada breadboard dengan tombol saja sudah cukup.
   
4. Jika salah satu LED segmen tidak menyala, apa saja kemungkinan penyebabnya dari sisi hardware maupun software?

   - **Hardware:** Ada kemungkinan bahwa led tersebut rusak, koneksi di breadboard yang tidak pas, resistor yang teputus, atau dari pin arduino tersebut yang bermasalah. Selain itu ada kemungkinan juga tegangan power suply yang tidak stabil.

    - **Software:** Kemungkinan terdapat kesalahan nilai pada array `digitPattern` atau urutan pin di `segmentPins[]` tidak sesuai dengan wiring pada pin digital arduino. Pastikan juga apakah 7-segment yang digunakan jenisnya common cathode atau common anode.
   
5. Modifikasi rangkaian dan program dengan dua push button yang berfungsi sebagai penambahan (increment) dan pengurangan (decrement) pada sistem counter dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!
    ```cpp
   #include <Arduino.h>

    // =================== PIN ==================
    const int segmentPins[8] = {7, 6, 5 ,11, 10, 8, 9, 4};
    // a b c d e f g dp

    const int btnUp = 3;               // Pin tombol increment (sudah ada)
    const int btnDown = 2;             // [UBAH] Tambah pin tombol decrement di pin 2
    
    // ================= DATA =================
    // CC: 1 = ON, 0 = OFF
    byte digitPattern[16][8] = {
    
    {1,1,1,1,1,1,0,0}, //0
    {0,1,1,0,0,0,0,0}, //1
    {1,1,0,1,1,0,1,0}, //2
    {1,1,1,1,0,0,1,0}, //3
    {0,1,1,0,0,1,1,0}, //4
    {1,0,1,1,0,1,1,0}, //5
    {1,0,1,1,1,1,1,0}, //6
    {1,1,1,0,0,0,0,0}, //7
    {1,1,1,1,1,1,1,0}, //8
    {1,1,1,1,0,1,1,0}, //9
    {1,1,1,0,1,1,1,0}, //A
    {0,0,1,1,1,1,1,0}, //b
    {1,0,0,1,1,1,0,0}, //C
    {0,1,1,1,1,0,1,0}, //d
    {1,0,0,1,1,1,1,0}, //E
    {1,0,0,0,1,1,1,0}  //F
    };
    
    int currentDigit = 0;
    
    // state sebelumnya (untuk edge detection)
    bool lastUpState = HIGH;           // State tombol increment (sudah ada)
    bool lastDownState = HIGH;         // [UBAH] Tambah variable untuk menyimpan state tombol decrement
    
    // ============= FUNCTION ============
    void displayDigit(int num)
    {
      for(int i=0;i<8;i++)
      {
        digitalWrite(segmentPins[i], !digitPattern[num][i]);
      }
    }
    
    // ================= SETUP ============
    void setup() {
    for(int i=0;i<8;i++)
    {
      pinMode(segmentPins[i], OUTPUT);  // Set pin segment sebagai output
    }
    
    pinMode(btnUp, INPUT_PULLUP);       // Set pin 3 (tombol increment) dengan pull-up
    pinMode(btnDown, INPUT_PULLUP);     // [UBAH] Set pin 2 (tombol decrement) dengan pull-up
    
    displayDigit(currentDigit);         // Tampilkan angka 0 di awal
    }
    
    // ========== LOOP ============
    
    void loop() {
      bool upState = digitalRead(btnUp);      // Baca status tombol increment
      bool downState = digitalRead(btnDown);  // [UBAH] Baca status tombol decrement
    
      // ======== UP (increment) ===========
      if(lastUpState == HIGH && upState == LOW)  // Deteksi tombol increment ditekan (transisi dari HIGH ke LOW)
      {
        currentDigit++;                 // Tambah 1 ke counter
        if(currentDigit > 15) currentDigit = 0;  // Reset ke 0 jika melebihi F (15)
        displayDigit(currentDigit);     // Tampilkan angka baru
      }
    
      // ======== DOWN (decrement) ===========
      // [UBAH] Bagian baru: deteksi tombol decrement
      if(lastDownState == HIGH && downState == LOW)  // Deteksi tombol decrement ditekan (transisi dari HIGH ke LOW)
      {
        currentDigit--;                 // Kurang 1 dari counter
        if(currentDigit < 0) currentDigit = 15;     // Jika kurang dari 0, reset ke F (15)
        displayDigit(currentDigit);     // Tampilkan angka baru
      }
    
      lastUpState = upState;            // Simpan state tombol increment untuk loop berikutnya
      lastDownState = downState;        // [UBAH] Simpan state tombol decrement untuk loop berikutnya
    
    }
    ```
