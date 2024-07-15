// int a[3] = 459;
char hexString[5];
int a = 9;  
int b = 32; 

unsigned char data[3] = {0x30, 0x31, 0x32};
void setup() {
  Serial.begin(9600);

}

void loop() {
  
  // sprintf(hexString, "0x%02X", a);

  // String hexString = "0x" + String(a, HEX);

  sprintf(hexString, "0x%02X", a + '0');
  // int b = a[1];

  // data[2] = hexString;
  Serial.println(hexString);
  long intVal = strtol(hexString, NULL, 16);
 
  char charVal = static_cast<char>(intVal);

// Use the character value
  Serial.println(charVal);
 

  // Serial.println(data[2]);
  // Serial.println(hexString[1]);
  delay(1000);

}
