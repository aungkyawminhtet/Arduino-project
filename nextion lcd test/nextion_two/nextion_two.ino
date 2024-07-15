#include<Nextion.h>
const int led_pin = 17;

NexButton bOn = NexButton(1, 4, "bon");
NexButton bOff = NeBbutton(1, 5, "boff");

// NexTouch *nex_listen_list[] = {
//   &bOn,
//   &bOff,
//   NULL
// };

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);

}

void loop() {

}
