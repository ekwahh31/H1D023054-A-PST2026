# PERTANYAAN PRAKTIKUM PEMOGRAMAN SISTEM TERTANAM - Komunikasi Task

## Pertanyaan
1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!
2. Apakah program ini berpotensi mengalami race condition? Jelaskan!
3. Modifikasilah program dengan menggunakan sensor DHT sesungguhnya sehingga informasi yang ditampilkan dinamis. Bagaimana hasilnya? Jelaskan program pada file README.md.


## Jawaban
1. Kedua task berjalan bergantian. Task read_data membaca sensor dan mengirim data ke queue setiap 100ms, sedangkan task display menunggu untuk menerima dan menampilkan data. RTOS scheduler membagi waktu prosesor untuk kedua task secara bergantian dengan cepat melalui context switching, sehingga terlihat seolah-olah berjalan bersamaan padahal sebenarnya satu per satu.

2. Tidak, program ini aman dari race condition karena menggunakan queue sebagai mekanisme komunikasi yang thread-safe. Queue secara otomatis mengatur sinkronisasi antara kedua task, memastikan hanya satu task yang bisa akses data pada waktu yang sama. Jika langsung mengakses variable global tanpa queue, maka akan terjadi race condition karena kedua task bisa mengubah data bersamaan dan menyebabkan data corrupt.

3. Modifikasi Kode 
    ```cpp
    #include <Arduino_FreeRTOS.h>
    #include <queue.h>
    #include <DHT.h>

    // Konfigurasi DHT sensor
    #define DHTPIN 2           // Pin digital untuk DHT sensor
    #define DHTTYPE DHT22      
    DHT dht(DHTPIN, DHTTYPE);

    struct readings {
    float temp;
    float h;
    };

    QueueHandle_t my_queue;

    void setup() {
    Serial.begin(9600);
    dht.begin();  // Inisialisasi sensor DHT

    my_queue = xQueueCreate(1, sizeof(struct readings));

    xTaskCreate(read_data, "read sensors", 128, NULL, 0, NULL);
    xTaskCreate(display, "display", 128, NULL, 0, NULL);
    }

    void loop() {}

    // Task membaca data dari sensor DHT
    void read_data(void *pvParameters) {
    struct readings x;

    for(;;) {
        // Baca nilai temperatur dan humidity dari sensor DHT
        x.temp = dht.readTemperature();
        x.h = dht.readHumidity();

        // Cek apakah pembacaan berhasil
        if(!isnan(x.temp) && !isnan(x.h)) {
        xQueueSend(my_queue, &x, portMAX_DELAY);
        } else {
        Serial.println("Gagal membaca sensor DHT!");
        }
        
        vTaskDelay(2000);  // Baca setiap 2 detik (DHT memerlukan waktu min 2 detik)
    }
    }

    // Task menampilkan data
    void display(void *pvParameters) {
    struct readings x;

    for(;;) {
        if(xQueueReceive(my_queue, &x, portMAX_DELAY) == pdPASS) {
        Serial.print("Temperatur = ");
        Serial.print(x.temp);
        Serial.println(" °C");

        Serial.print("Humidity = ");
        Serial.print(x.h);
        Serial.println(" %");
        
        Serial.println("---");
        }
    }
    }
    ```
    ### Penjelasan Modifikasi Kode
    Task read_data membaca nilai temperatur dan humidity dari sensor DHT22 secara real-time menggunakan fungsi `dht.readTemperature()` dan `dht.readHumidity()`. Data kemudian dicek apakah valid (tidak error/NaN), lalu dikirim ke queue. Sementara itu, task display menunggu data dari queue dan langsung menampilkannya. Kedua task berjalan bergantian dengan aman tanpa race condition karena menggunakan queue sebagai komunikasi yang thread-safe.

    ### Penjelasan Hasil
    Serial monitor akan menampilkan data dinamis yang berubah setiap 2 detik sesuai kondisi lingkungan, misal:
    ```
    Temperatur = 25.50 °C
    Humidity = 60.25 %
    ---
    Temperatur = 25.52 °C
    Humidity = 60.30 %
    ```