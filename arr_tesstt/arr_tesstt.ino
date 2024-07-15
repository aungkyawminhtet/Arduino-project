

#define MAX_ARRAY_SIZE 100 // Define the maximum size of the array

char receivedData[MAX_ARRAY_SIZE]; // Array to store received data
int dataLength = 0; // Current data length in the array

void setup() {
  Serial.begin(115200);  // Initialize Serial communication at 115200 baud rate
}

void loop() {
  // Sender
  if (Serial.availableForWrite()) {
    Serial.write("Hello, ESP32!"); // Send a message
    delay(1000); // Wait for 1 second before sending the next message
  }
  
  // Receiver
  if (Serial.available()) {
    char receivedChar = Serial.read(); // Read the incoming character
    
    // Check if the array has space to store the received character
    if (dataLength < MAX_ARRAY_SIZE - 1) {
      receivedData[dataLength] = receivedChar; // Append the received character to the array
      dataLength++;
      receivedData[dataLength] = '\0'; // Null-terminate the array for string handling
    }
    
    Serial.print("Received Data: ");
    Serial.println(receivedData); // Print the received data array
  }
}
