String inputString = "";         // a string to hold incoming data

void setup() {
  Serial.begin(9600);
  inputString.reserve(200);
}

void loop() {
  while (Serial.available()) {
    delay(100);
    char inChar = (char)Serial.read(); 
    inputString += inChar;
    if (inChar == '\n') {
      Serial.print(inputString);
      inputString = "";
    } 
  }
}
