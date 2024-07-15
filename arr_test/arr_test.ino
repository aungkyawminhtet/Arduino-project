char arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

int arr_length = sizeof(arr) / sizeof(arr[0]);

#define max_size 50

int datalength = 0;

int i = 0;

char arr_data[max_size];

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  // Serial.print("Arr length is => ");
  // Serial.println(arr);
  // delay(1000);

  for(i ; i < arr_length ; i++){
    Serial.print("From arr => ");
    Serial.println(arr[i]);

    arr_data[i] = arr[i];

    Serial.println(arr_data[i]);
    if(arr_data[i] == 'h'){
      ak();
    }
  }

}

void ak(){
  Serial.println("This is ak function");
  int arr_data_length = sizeof(arr_data) / sizeof(arr_data[0]);
  Serial.println(arr_data_length);
  Serial.println(arr_data);

  if(arr_data[0] == 'a' && arr_data[5] == 'f'){
    Serial.println("I Found a and f");
  }

  for(int x=0 ; x < 8 ; x++){
    // Serial.print("From arr => ");
    Serial.print(x);
    Serial.print(" ");
    Serial.print(arr_data[x]);
    Serial.print("  ");
  }
}
