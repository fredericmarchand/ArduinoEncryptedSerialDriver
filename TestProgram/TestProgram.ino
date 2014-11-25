#include <EncSoftwareSerial.h>
#include <des.h>

DES des;
EncSoftwareSerial mySerial(10, 11, "ABCDEFGH"); // RX, TX

void setup() {
  mySerial.begin(9600);
}

void loop() {
  delay(5000);
  mySerial.write("ABCDEFGHIJKLMNOP", 16);
  delay(5000);
  mySerial.write("STUVWXYZ", 8);
  delay(5000);
  mySerial.write("LMNOP", 5);
  delay(5000);
  mySerial.write("HELLOWORLD", 10);
}
