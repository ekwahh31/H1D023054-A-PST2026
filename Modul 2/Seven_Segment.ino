#include <Arduino.h>
// Library Arduino untuk fungsi digitalWrite, pinMode, delay, dll

//7-Segment Display (Efficient Version)
//Display 0 - 9 and A - F

// Array untuk menyimpan pin Arduino yang terhubung ke masing-masing segment
const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};
// Urutan: a b c d e f g dp (dp = decimal point)

// Segment pattern for 0-F
// urutan segmen: a b c d e f g dp
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

// Fungsi menampilkan digit pada 7-segment display
void displayDigit(int num)
{
  // Loop untuk mengatur setiap segment (8 segment: a,b,c,d,e,f,g,dp)
  for(int i=0;i<8;i++)
  {
    // Kirim nilai inverse dari pattern ke pin segment (! untuk logika inverse)
    digitalWrite(segmentPins[i], !digitPattern[num][i]);
  }
}

void setup()
{
  // Loop untuk mengatur semua pin segment sebagai output
  for(int i=0;i<8;i++)
  {
    // Set pin segment ke mode OUTPUT
    pinMode(segmentPins[i], OUTPUT);
  }
}

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