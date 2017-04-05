#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
using namespace std;

void init();
void createLetterMatrix();
void createRandomNumberString();
string createEncryptedString(string msg);
string createDecryptedString(string msg);
char digitToChar(int n);
int charToDigit(char c);
int charToSingleDigit(char c);
void debug(string msg);

string letters("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
int length = letters.length();
char **letterMatrix = new char*[10];
string randNumStr;
string encryptStr;
string decryptStr;

int main()
{
  init();

  cout << "enter cipher message: "<< endl;
  string msg;
  cin >> msg;

  encryptStr = createEncryptedString(msg);
  decryptStr = createDecryptedString(encryptStr);
  
  return 0;
}

void init()
{
  createLetterMatrix();
  createRandomNumberString();  
}

void createLetterMatrix()
{
  //letters -> letter matrix
  letterMatrix[0] = new char[10];
  int a = 0;
  int b = 0;
  
  for(int i = 0; i < length; i++)
    {
      letterMatrix[a][b] = letters.at(i);
      
      if(b == 9)
	{
	  letterMatrix[++a] = new char[10];
	  b = 0;
	}
      else
	{
	  ++b;
	}
    }

  debug("letter matrix created");
}

void createRandomNumberString()
{
  string hexStr;
  string numStr;
  ifstream infile("random.hex");
  
  //check file access
  if(infile.is_open())
    {
      //file content -> string
      getline(infile, hexStr);
     
      //iterate string
      //hex char -> number
      //number -> 2nd string
      string::iterator it;
      for(it = hexStr.begin(); it < hexStr.end(); it++)
	{
	  stringstream ss;
	  ostringstream oss;
	  int tmp;
	  char c = *it;
	  ss << c;
	  ss >> hex >> tmp;
	  oss << tmp;
	  randNumStr += oss.str();
	}
      
      infile.close();
      
      debug("random number string created");
    }
  else
    {
      debug("cant open file");
    }
}

//encrypt
//message -> literal digits
//literal digits -> encrypted digits
//encrypted digits -> encrypted message
string createEncryptedString(string msg)
{
  string tmp;
  
  for(int i = 0; i < msg.length(); i++)
    {
      char c = randNumStr.at(i);
      int encryptedDigit = charToDigit(msg[i]) + atoi(&c);
      tmp += digitToChar(encryptedDigit);
    }

  debug("encrypted: " + tmp);
  return tmp;
}

//decrypt
//encrypted message -> literal digits
//literal digits -> decrypted digits
//decrypted digits -> decrypted message
string createDecryptedString(string msg)
{
  string tmp;
  
  for(int i = 0; i < msg.length(); i++)
    {
      const char c = randNumStr.at(i);
      int decryptedDigit = charToDigit(msg[i]) - atoi(&c); 

      //assure digit in letter range
      if(decryptedDigit < 0)
	{
	  decryptedDigit += length;
	}

      tmp += digitToChar(decryptedDigit); 
    }
  
  debug("decrypted: " + tmp);
  return tmp;
}

//digit -> char
char digitToChar(int n)
{
  //assure digit in letter range
  while(n >= length)
    {
      n -= length;
    }
  
  return letters.at(n);
}

//char -> digit
int charToDigit(char c)
{
  for(int i = 0; i < length; i++)
    {
      if(c == letters.at(i))
	{
	  return i;
	}
    }

  debug("no match found letter");
  return -1;
}

//char -> single digit
int charToSingleDigit(char c)
{
  for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 10; j++)
	{
	  if(letterMatrix[i][j] == c)
	    {
	      return j;
	    }
	}
    }
  
  debug("no match found letter matrix");
  return -1;
}

void debug(string msg)
{
  cout << "DEBUG: " << msg << endl;
}
