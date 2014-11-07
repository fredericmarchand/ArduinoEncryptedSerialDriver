//Input Text through console
//Transmit through serial
//On receive transmit the inverse
//Print encryption step on console

String inputString = "";

void setup() {
  Serial.begin(9600);
  inputString.reserve(200);
}

void loop() 
{
  delay(5000);
  Serial.write("Random Text\r\n");
}





