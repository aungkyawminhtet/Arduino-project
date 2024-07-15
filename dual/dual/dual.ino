HardwareSerial Sender(1);
HardwareSerial Receiver(2);

#define sender_tx_pin 15
#define sender_rx_pin 14

#define receiver_tx_pin 17
#define receiver_rx_pin 16

void setup() {
  Serial.begin(9600);
  Sender.begin(9600, SERIAL_8N1, sender_tx_pin, sender_rx_pin);
  Receiver.begin(9600, SERIAL_8N1, receiver_tx_pin, receiver_rx_pin);

}

void loop() {
  Sender.println("This is from sender");
  while(Receiver.available()){
    char data = Receiver.read();
    Serial.println(data);
  }

  delay(1000);

}
