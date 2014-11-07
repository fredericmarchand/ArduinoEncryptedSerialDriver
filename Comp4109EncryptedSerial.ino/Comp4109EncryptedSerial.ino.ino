//Input Text through console
//Transmit through serial
//On receive transmit the inverse
//Print encryption step on console

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  Serial.begin(9600);
  inputString.reserve(200);
}

void loop() 
{
  delay(5000); 
  Serial.write("Hello World\r\n");
}





