#include <EncSoftwareSerial.h>
#include <des.h>

EncSoftwareSerial mySerial(10, 11, "ABCDEFGH"); // RX, TX

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  delay(5000);
  Serial.println("ABCDEFGHIJKLMNOP");
  mySerial.write("ABCDEFGHIJKLMNOP", 16);
  delay(5000);
  Serial.println("STUVWXYZ");
  mySerial.write("STUVWXYZ", 8);
  delay(5000);
  Serial.println("LMNOP");
  mySerial.write("LMNOP", 5);
  delay(5000);
  Serial.println("HELLOWORLD");
  mySerial.write("HELLOWORLD", 10);
  delay(5000);
  Serial.println("I love cryptography");
  mySerial.write("I love cryptography", 19);
}
