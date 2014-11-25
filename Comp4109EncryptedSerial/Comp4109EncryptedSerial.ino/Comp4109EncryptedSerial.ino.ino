//Initiate serial
//Input Text through console
//Transmit through serial
//On receive transmit the inverse
//Print encryption step on console
#include <des.h>
#include <EncSoftwareSerial.h>

EncSoftwareSerial mySerial(10, 11, "ABCDEFGH"); // RX, TX
char cipher[17];
char plain[17];

DES des;
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600); 
}

void loop() {
  static int counter = 0;
  int charCount = 0;

  memset(cipher, '\0', 16);
  memset(plain, '\0', 16);
    
  while (!mySerial.available());
  delay(100);
  while (mySerial.available()) 
  {
    char inChar = (char)mySerial.read(); 
    cipher[charCount++] = inChar; 
    if (charCount == 16)
    {
       Serial.println(cipher);
       des.tripleDESDecrypt(plain, cipher, "ABCDEFGH", "ABCDEFGH", "ABCDEFGH");
       for (int i = 0; i < 16; ++i)
       {
         if (plain[i] != '0')
           Serial.print(plain[i]);
       }
       Serial.println();
       charCount = 0;
    }
  }
    if (charCount == 8)
    {
       Serial.println(cipher);
       des.tripleDESDecrypt(plain, cipher, "ABCDEFGH", "ABCDEFGH", "ABCDEFGH");
       for (int i = 0; i < 8; ++i)
       {
         if (plain[i] != '0')
           Serial.print(plain[i]);
       }
       Serial.println();
       charCount = 0;
    }
}
