#ifndef DES_H
#define DES_H

#include "Arduino.h"

class DES {

private:

    struct KeySet{
        char k[6]; 
    };

	char key1[8];
	char key2[8];
	char key3[8];
	
    void encryptBlock(char *plaintext, char *finalCiphertext,  KeySet *keyset, char mode);
    void generateSubKeys(const char *key, KeySet *keyset);

public: 

	DES();
    DES(char *newkey1);
	DES(char *newkey1, char *newkey2);
	DES(char *newkey1, char *newkey2, char *newkey3);
    ~DES();
    void DESEncrypt(char *ciphertext, char *plaintext);
    void DESDecrypt(char *plaintext, char *ciphertext);
    void tripleDESEncrypt(char *ciphertext, char *plaintext);
    void tripleDESDecrypt(char *plaintext, char *ciphertext);
    void generateKey(char* key); 

};

#endif
