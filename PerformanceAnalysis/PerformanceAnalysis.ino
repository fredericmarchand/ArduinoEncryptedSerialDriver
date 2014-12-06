#include <des.h>

DES des;
char key1[8];
char key2[8];
char key3[8];
int blocks;
unsigned long total_time_ticks;
unsigned long time_a;
unsigned long time_b;

int times[7] = {4, 8, 16, 32, 64, 128, 256};
int index;

void generateRandomBlocks(char *output, int blocks)
{
    char temp[2];
    for (int i = 0; i < blocks*8; ++i)
    {
        sprintf(temp, "%d", rand()%256);
        output[i] = temp[0];
    }
}

void setup()
{
    Serial.begin(9600);
    des.generateKey(key1);
    des.generateKey(key2);
    des.generateKey(key3);
    des = DES(key1, key2, key3);
    index = 0;
}

void loop()
{
  blocks = times[index++];
  if (index > 6) index = 0;
  char input[blocks*8];
  char output[blocks*8];
 
  generateRandomBlocks(input, blocks);
 
  time_a = micros();
  des.tripleDESEncrypt(output, input);
  time_b = micros();
  
  total_time_ticks = (time_b - time_a);
  if (index == 0)
    Serial.print(times[6]);
  else
    Serial.print(times[index-1]);
  Serial.print( " - Time: ");
  Serial.print(total_time_ticks);
  Serial.println(" us");
  delay(1000);
}
