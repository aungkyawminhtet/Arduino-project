#include <WiFi.h>
int led_pin = 2;

const char* ssid = "Digital Engineering Tech";
const char* password = "1313373290";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while( WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wifi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();

}

void loop() {
  WiFiClient client = server.available();

  if(client){
    Serial.println("New Client is connected.");

    String current_line = "";

    while(client.connected()){

      if(client.available()){
        char c = client.read();
        Serial.write(c);

        if(c == '\n'){

          if(current_line.length() == 0){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.print("Click <a href=\"/ak\">Here</a> to trun on LED on pin 2 on.<br>");
            client.print("Click <a href=\"/aa\">Here</a> to trun on LED on pin 2 on.<br>");
            
            client.println();
            break;

          }else{
            current_line = "";
          }

        }else if( c != '\r'){
          current_line += c;
        }
        // Serial.print("form current_line => ");
        // Serial.println(current_line);

        if(current_line.endsWith("GET /ak")){
          digitalWrite(led_pin, HIGH);
        }
        if(current_line.endsWith("GET /aa")){
          digitalWrite(led_pin, LOW);
        }

      }
      
    }
    client.stop();
    Serial.println("Client Disconnected");

  }

}

void wifi_start(){

}


