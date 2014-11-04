/*
 * Frederic Marchand
 * 100817579
 * Comp4109
 * S-DES
 */

#include <string.h>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

/* Defines */
#define KEY_SIZE 10
#define TEXT_SIZE 8
#define IP_SIZE 8

/* Types */
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

/* Global variables */
static string key;
static string plain;
static string cipher;
static string keys[2];

/* Local Function Prototypes */
static bool validateBinary(string input);
static int binaryToDecimal(string input);
static string decimalToBinary(int input);
static bool setCiphertext(string ciphertext);
static bool setPlaintext(string plaintext);
static bool setKey(string newKey);
static string IP(string input);
static string inverseIP(string input);
static string P10(string input);
static string P8(string input);
static string sBox2(string input, uint16_t sbox);
static string getLeft(string input);
static string getRight(string input);
static string leftShift(string input);


/* Function Implementations */

static void generateKeys()
{
    string currentKey = key;

    if (currentKey.size() != KEY_SIZE)
    {
        return;
    }

    currentKey = P10(currentKey);

    string keyLeft = leftShift(getLeft(currentKey));
    string keyRight = leftShift(getRight(currentKey));

    keys[0] = P8(keyLeft + keyRight);

    keyLeft = leftShift(keyLeft);
    keyRight = leftShift(keyRight);
    keyLeft = leftShift(keyLeft);
    keyRight = leftShift(keyRight);

    keys[1] = P8(keyLeft + keyRight);
}

// Initial Permutation
static string IP(string input)
{
    uint32_t table[IP_SIZE] = {2,6,3,1,4,8,5,7};
    string retVal("");

    for (uint32_t i = 0; i < IP_SIZE; ++i)
    {
        retVal += input[table[i]-1];
    }
    return retVal;
}

// Inverse Initial Permutation 
static string inverseIP(string input)
{
    uint32_t table[IP_SIZE] = {4,1,3,5,7,2,8,6};
    string retVal("");

    for (uint32_t i = 0; i < IP_SIZE; ++i)
    {
        retVal += input[table[i]-1];
    }
    return retVal;
}

// P10
static string P10(string input)
{
    uint32_t table[KEY_SIZE] = {3,5,2,7,4,10,1,9,8,6};
    string retVal = "";

    for (uint32_t i = 0; i < KEY_SIZE; ++i)
    {
        retVal += input[table[i]-1];
    }
    return retVal;
}

// P8
static string P8(string input)
{
    uint32_t table[TEXT_SIZE] = {6,3,7,4,8,5,10,9};
    string retVal("");

    for (uint32_t i = 0; i < TEXT_SIZE; ++i)
    {
        retVal += input[table[i]-1];
    }
    return retVal;
}

// left shift
static string leftShift(string input)
{
    string retVal("");

    if (input.size() == 0)
    {
        return retVal;
    }

    for (uint32_t i = 1; i < input.size(); ++i)
    {
        retVal += input[i];
    }

    retVal += input[0];

    return retVal;
}

// XOR
static string XOR(string input, string key)
{
    string retVal("");

    if (input.size() != key.size())
    {
        return retVal;
    }
    
    for (uint32_t i = 0; i < input.size(); ++i)
    {
        retVal += (input[i] ^ key[i]) ? "1" : "0";
    }
    return retVal;
}

// SBOX
static string sBox(string input, int round)
{
    uint32_t table[TEXT_SIZE] = {4,1,2,3,2,3,4,1};
    string temp("");

    for (uint32_t i = 0; i < TEXT_SIZE; ++i)
    {
        temp += input[table[i]-1];
    }
    input = temp;

    input = XOR(input, keys[round]);

    string leftHalf = getLeft(input);
    leftHalf = sBox2(leftHalf, 0);

    string rightHalf = getRight(input);
    rightHalf = sBox2(rightHalf, 1);

    string retVal = leftHalf + rightHalf;

    uint32_t table2[4] = {2,4,3,1};
    temp = "";

    for (uint32_t i = 0; i < 4; ++i)
    {
        temp += retVal[table2[i]-1];
    }

    retVal = temp;

    return retVal;
}

// SBOX helper
static string sBox2(string input, uint16_t sbox)
{
    string retVal("");
    string rowValue("");
    string columnValue("");
    vector< vector<string> > box;
    int col;
    int row;

    if (input.size() != 4)
    {
        return retVal;
    }

    if (sbox == 0)
    {
        vector<string> row;

        row.push_back("01");
        row.push_back("00");
        row.push_back("11");
        row.push_back("10");
        box.push_back(row);

        row.clear();
        row.push_back("11");
        row.push_back("10");
        row.push_back("01");
        row.push_back("00");
        box.push_back(row);

        row.clear();
        row.push_back("00");
        row.push_back("10");
        row.push_back("01");
        row.push_back("11");
        box.push_back(row);

        row.clear();
        row.push_back("11");
        row.push_back("01");
        row.push_back("11");
        row.push_back("10");
        box.push_back(row);
    } 
    else if (sbox == 1) 
    {
        vector<string> row;

        row.push_back("00");
        row.push_back("01");
        row.push_back("10");
        row.push_back("11");
        box.push_back(row);

        row.clear();
        row.push_back("10");
        row.push_back("00");
        row.push_back("01");
        row.push_back("11");
        box.push_back(row);

        row.clear();
        row.push_back("11");
        row.push_back("00");
        row.push_back("01");
        row.push_back("00");
        box.push_back(row);

        row.clear();
        row.push_back("10");
        row.push_back("01");
        row.push_back("00");
        row.push_back("10");
        box.push_back(row);
    } 
    else 
    {
        return retVal;
    }

    columnValue += input[1];
    columnValue += input[2];
    col = binaryToDecimal(columnValue);

    rowValue += input[0];
    rowValue += input[3];
    row = binaryToDecimal(rowValue);

    return box[row][col];
}

// get left half
static string getLeft(string input)
{
    string retVal("");

    if (input.size() == 0)
    {
        return retVal;
    }

    for (uint32_t i = 0; i < input.size()/2; ++i)
    {
        retVal += input[i];
    }

    return retVal;
}

// get right half
static string getRight(string input)
{
    string retVal("");

    if(input.size() == 0)
    {
        return retVal;
    }

    for (uint32_t i = floor(input.size()/2); i < input.size(); ++i)
    {
        retVal += input[i];
    }

    return retVal;
}

// Encryption function
static string sdesEncrypt()
{
    string retVal("");
    string leftSide;
    string rightSide;
    string temp;
    string text;

    if (key.size() != KEY_SIZE || plain.size() != TEXT_SIZE)
    {
        return retVal;
    }

    text = plain;
    text = IP(text);

    leftSide = getLeft(text);
    rightSide = getRight(text);

    leftSide = XOR(leftSide, sBox(rightSide, 0));

    temp = leftSide;
    leftSide = rightSide;
    rightSide = temp;

    leftSide = XOR(leftSide, sBox(rightSide, 1));    

    text = leftSide + rightSide;
    retVal = cipher = inverseIP(text);

    return retVal;
}

// Decryption function
static string sdesDecrypt()
{
    string retVal("");
    string leftSide;
    string rightSide;
    string temp;
    string text;

    if (key.size() != KEY_SIZE || cipher.size() != TEXT_SIZE)
    {
        return retVal;
    }

    text = cipher;
    text = IP(text);

    leftSide = getLeft(text);
    rightSide = getRight(text);

    leftSide = XOR(leftSide, sBox(rightSide, 1));

    temp = leftSide;
    leftSide = rightSide;
    rightSide = temp;

    leftSide = XOR(leftSide, sBox(rightSide, 0));    

    text = leftSide + rightSide;
    retVal = plain = inverseIP(text);

    return retVal;
}

static bool setKey(string newKey)
{
    if (!validateBinary(newKey) || newKey.size() != KEY_SIZE)
    {
        cerr << "Invalid key" << endl;
        return false;
    }
    key = newKey;
    generateKeys();
    return true;
}

static bool setPlaintext(string plaintext)
{ 
    if (!validateBinary(plaintext) || plaintext.size() != TEXT_SIZE)
    {
        cerr << "Invalid plaintext" << endl;
        return false;
    }
    plain = plaintext; 
    return true;
}

static bool setCiphertext(string ciphertext)
{ 
    if (!validateBinary(ciphertext) || ciphertext.size() != TEXT_SIZE)
    {
        cerr << "Invalid ciphertext" << endl;
        return false;
    }
    cipher = ciphertext;
    return true;
}

static string decimalToBinary(int input)
{
    if (input == 0) 
    {
        return "0";
    }
    if (input == 1) 
    {
        return "1";
    }

    if ((input % 2) == 0)
    {
        return decimalToBinary(input / 2) + "0";
    }
    else
    {
        return decimalToBinary(input / 2) + "1";
    }
}

static int binaryToDecimal(string input)
{
    int result = 0, pow = 1;
    for (int i = input.length() - 1; i >= 0; --i, pow <<= 1)
    {
        result += (input[i] - '0') * pow;
    }
    return result;
}

static bool validateBinary(string input)
{
    if (input.size() == 0)
    {
        return false;
    }

    for (uint32_t i = 0; i < input.size(); ++i)
    {
        if (input[i] != '0' && input[i] != '1')
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cerr << "Not enough parameters." << endl;
        return 0;
    }

    string mode = argv[1];
    string buffer = argv[2];
    string key = argv[3];

    if (mode == "e" || mode == "E")
    {
        if (!setKey(key))
        {
            return 0;
        }
        if (!setPlaintext(buffer))
        {
            return 0;
        }
        cout << "Plaintext:\t" << buffer << "\nKey:\t\t" << key << "\nCiphertext:\t";
        cout << sdesEncrypt() << endl;
    } 
    else if (mode == "d" || mode == "D") 
    {
        if (!setKey(key))
        {
            return 0;
        }
        if (!setCiphertext(buffer))
        {
            return 0;
        }
        cout << "Ciphertext:\t" << buffer << "\nKey:\t\t" << key << "\nPlaintext:\t";
        cout << sdesDecrypt() << endl;
    } 
    else 
    {
        cerr << "Invalid mode!" << endl;
        return 0;
    }

    return 0;
}

