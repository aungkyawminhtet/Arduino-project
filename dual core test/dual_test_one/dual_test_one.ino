TaskHandle_t Task1;
TaskHandle_t Task2;

const int led_pin = 5;
const int led = 2;

void setup() {
  Serial.begin(115200);
  // Serial.println();
  // Serial.println(xPortGetCoreID());
  pinMode(led, OUTPUT);
  pinMode(led_pin, OUTPUT);

  xTaskCreatePinnedToCore(Task1Code, "Task1", 10000, NULL, 1, &Task1, 0);
  xTaskCreatePinnedToCore(Task2Code, "Task2", 10000, NULL, 1, &Task2, 1);
}

void Task1Code(void* Parameters) {
  Serial.print("Croe is running in ID => ");
  Serial.println(xPortGetCoreID());
  String data = "";
  for (;;) {
     Serial.println("hello core 0");
    delay(1000);
  }
}

void Task2Code(void* Parameters) {
  Serial.print("Core is running in ID => ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    ak();
  }
}

void ak() {
  Serial.println("ak is running in core 1");
  delay(500);
  // digitalWrite(led_pin, HIGH);
  // // delay(1000);
  // digitalWrite(led_pin, LOW);
  // delay(1000);
}

void loop() {
}
