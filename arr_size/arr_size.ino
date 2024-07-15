int myArray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Example array

// Calculate the total number of elements in the array
int totalElements = sizeof(myArray) / sizeof(myArray[0]);
int a = 2;
int b = 9;

int c,d;

void setup() {
  Serial.begin(9600);
}

void loop() {


  // Serial.print("Total Elements in the Array: ");
  // Serial.println(totalElements);

  for(int i = 0 ; i < totalElements ; i++){
    Serial.print("Arr data => ");
    Serial.println(myArray[i]);

    if(myArray[i] == a && myArray[i] == b){
      Serial.println("Found 2 and 9");
    }else{
      Serial.println("Not Found data");
    }
  } 

}
