#include <EncSoftwareSerial.h>

#include <des.h>

EncSoftwareSerial mySerial(10, 11, "ABCDEFGH"); // RX, TX
char cipher[64];
char plain[64];

DES des;
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600); 
  des = DES("ABCDEFGH");
}

void loop() {
  static int counter = 0;
  int charCount = 0;

  memset(cipher, '\0', 64);
  memset(plain, '\0', 64);
    
  while (!mySerial.available());
  delay(100);
  while (mySerial.available()) 
  {
    char inChar = (char)mySerial.read(); 
    cipher[charCount++] = inChar; 
  }
  
  if (charCount == 24)
  {
     Serial.println(cipher);
     des.tripleDESDecrypt(plain, cipher);
     for (int i = 0; i < 24; ++i)
     {
       if (plain[i] != '0')
         Serial.print(plain[i]);
     }
     Serial.println();
     charCount = 0;
  }
  
  if (charCount == 16)
  {
     Serial.println(cipher);
     des.tripleDESDecrypt(plain, cipher);
     for (int i = 0; i < 16; ++i)
     {
       if (plain[i] != '0')
         Serial.print(plain[i]);
     }
     Serial.println();
     charCount = 0;
  }
    
  if (charCount == 8)
  {
     Serial.println(cipher);
     des.tripleDESDecrypt(plain, cipher);
     for (int i = 0; i < 8; ++i)
     {
       if (plain[i] != '0')
         Serial.print(plain[i]);
     }
     Serial.println();
     charCount = 0;
  }
}
