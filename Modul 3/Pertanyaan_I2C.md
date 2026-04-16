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
| :--- | :--- | :--- |