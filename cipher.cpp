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
void log(string msg);
void log(int msg);

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
string createEncryptedString(string msg)
{
  int size = msg.length();
  vector<int> numMsgVec(size);

  //message -> literal digits
  debug("encrypted numeric msg: ");
  for(int i = 0; i < size; i++)
    {
      char c = msg[i];
      int n = charToDigit(c);
      numMsgVec[i] = n;
      
      log(n);
    }
  
  //literal digits -> encrypted digits
  vector<int> encryptNumMsgVec(size);
  debug("encrypted digits: ");
  for(int i = 0; i < size; i++)
    {
      const char c = randNumStr.at(i);
      encryptNumMsgVec[i] = numMsgVec[i] + atoi(&c);

      cout << "e: " << encryptNumMsgVec[i] << ", n: " << numMsgVec[i] << ", r: " << randNumStr.at(i) << endl;
    }
  
  //encrypted digits -> encrypted message
  string tmp;
  for(int i = 0; i < size; i++)
    {
      tmp += digitToChar(encryptNumMsgVec[i]);
    }
  
  debug("encrypted string: " + tmp);
  return tmp;
}

//decrypt
string createDecryptedString(string msg)
{
  int size = msg.length();
  vector<int> numMsgVec(size);

  //message -> literal digits
  debug("decrypted numeric msg: ");
  for(int i = 0; i < size; i++)
    {
      char c = msg[i];
      int n = charToDigit(c);
      numMsgVec[i] = n;

      log(n);
    }
  
  //literal digits -> decrypted digits
  vector<int> decryptNumMsgVec(size);
  debug("decrypted digits: ");
  for(int i = 0; i < size; i++)
    {
      const char c = randNumStr.at(i);
      decryptNumMsgVec[i] = numMsgVec[i] - atoi(&c);
      
      cout << "d: " << decryptNumMsgVec[i] << ", n: " << numMsgVec[i] << ", r: " << randNumStr.at(i) << endl;
    }

  //decrypted digits -> decrypted message
  string tmp;
  for(int i = 0; i < size; i++)
    {
      tmp += digitToChar(decryptNumMsgVec[i]);
    }
  
  debug("decrypt string: " + tmp);
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
  cout << "n: " << n << ", c: " << letters.at(n) << endl;
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

void log(string msg)
{
  cout << msg << endl;
}

void log(int msg)
{
  cout << msg << endl;
}
