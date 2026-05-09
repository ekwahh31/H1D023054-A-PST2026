# PERTANYAAN PRAKTIKUM PEMOGRAMAN SISTEM TERTANAM - Multitasking

## Pertanyaan
1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!
2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!
3. Modifikasilah program dengan menambah sensor (misalnya potensiometer), lalu gunakan nilainya untuk mengontrol kecepatan LED! Bagaimana hasilnya? Jelaskan program pada file README.md

## Jawaban
1. Ketiga task berjalan secara bergantian. Karena Arduino hanya memiliki satu prosesor, jadi FreeRTOS membagi waktu prosesor ke setiap task. Task 1 berjalan sebentar, lalu berhenti dan task 2 giliran berjalan. Setekah itu berganti ke task 3 dan kembali ke task 1. Karena prosesnya sangat cepat, maka seperti berjalan secara bersamaan.

2. Cara untuk menambahkan task ke 4 adalah
- lakukan deklaraso fungsi misal ``void TaskBlink3( void *pvParameters );``
- buat task di bagian setup() misal :
    ```cpp
        xTaskCreate(TaskBlink3, "task4", 128, NULL, 1, NULL);
    ```
- Terakhir tulis fungsi task pada bagian loop, misal :
    ```cpp
    void TaskBlink3(void *pvParameters) {
        pinMode(7, OUTPUT);  // Pin berbeda
        while(1) {
            Serial.println("Task4");
            digitalWrite(7, HIGH);
            vTaskDelay(400 / portTICK_PERIOD_MS);
            digitalWrite(7, LOW);
            vTaskDelay(400 / portTICK_PERIOD_MS);
        }
    }
    ```

3. Modifikasi kode dengan menambahkan potensioner
    ```cpp
    #include <Arduino_FreeRTOS.h>

    // Global variable untuk berbagi data antar task
    volatile int potValue = 0;

    void TaskBlink1( void *pvParameters );
    void TaskBlink2( void *pvParameters );
    void Taskprint( void *pvParameters );
    void TaskReadPotensio( void *pvParameters );  // Nambahin Potensioner

    void setup() {
    Serial.begin(9600);

    xTaskCreate(TaskBlink1, "task1", 128, NULL, 1, NULL);
    xTaskCreate(TaskBlink2, "task2", 128, NULL, 1, NULL);
    xTaskCreate(Taskprint, "task3", 128, NULL, 1, NULL);
    xTaskCreate(TaskReadPotensio, "task4", 128, NULL, 1, NULL);  // Nambahin Potensioner

    vTaskStartScheduler();
    }

    void loop() {}

    // Task membaca potensiometer dari pin A0
    void TaskReadPotensio(void *pvParameters) {
    while(1) {
        potValue = analogRead(A0);  // Baca nilai 0-1023
        Serial.print("Potensio: ");
        Serial.println(potValue);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    }

    // Task 1: LED dengan kecepatan dipengaruhi potensiometer
    void TaskBlink1(void *pvParameters) {
    pinMode(9, OUTPUT);

    while(1) {
        Serial.println("Task1");
        digitalWrite(9, HIGH);
        // Delay dari 50ms hingga 500ms sesuai nilai potensiometer
        int delayTime = map(potValue, 0, 1023, 50, 500);
        vTaskDelay(delayTime / portTICK_PERIOD_MS);
        
        digitalWrite(9, LOW);
        vTaskDelay(delayTime / portTICK_PERIOD_MS);
    }
    }

    // Task 2: LED dengan kecepatan tetap
    void TaskBlink2(void *pvParameters) {
    pinMode(8, OUTPUT);

    while(1) {
        Serial.println("Task2");
        digitalWrite(8, HIGH);
        vTaskDelay(300 / portTICK_PERIOD_MS);
        digitalWrite(8, LOW);
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
    }

    // Task 3: Print counter
    void Taskprint(void *pvParameters) {
    int counter = 0;

    while(1) {
        counter++;
        Serial.println(counter);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    }
    ```
    Ketika potensiometer diputar, LED pin 9 akan berkedip sesuai posisi potensiometer: putar ke awal (0°) = LED berkedip cepat (50ms), putar ke akhir (270°) = LED berkedip lambat (500ms). LED pin 8 tetap berkedip konstan, dan semua task berjalan bergantian tanpa gangguan.