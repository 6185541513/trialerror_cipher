#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>
using namespace std;

void createRandomNumberString();
string encryptMessage(string msg);
string decryptMessage(string msg);
char digitToChar(int n);
int charToDigit(char c);
string intToString(int n);
void debug(string msg);

string letters("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
int length = letters.length();
string randNumStr;

int main()
{
  createRandomNumberString();

  cout << "enter cipher message: "<< endl;
  string msg;
  cin >> msg;
  boost::to_upper(msg);
  
  string encryptedMsg = encryptMessage(msg);
  decryptMessage(encryptedMsg);
  
  return 0;
}

void createRandomNumberString()
{
  string hexStr;
  ifstream infile("random.hex");
  
  //check file access
  if(infile.is_open())
    {
      //file content -> string
      getline(infile, hexStr);
     
      //hex char -> numeric
      //numeric -> 2nd string
      string::iterator it;
      for(it = hexStr.begin(); it < hexStr.end(); it++)
	{
	  stringstream ss;
	  char c = *it;
	  ss << c;
	  int tmp;
	  ss >> hex >> tmp;
	  ostringstream convert;
	  convert << tmp;
	  randNumStr += convert.str();
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
string encryptMessage(string msg)
{
  string tmp;
  string dbugStr1;
  string dbugStr2;
  for(int i = 0; i < msg.length(); i++)
    {
      int n = charToDigit(msg[i]);
      char c = randNumStr.at(i);
      
      int encryptedDigit = n + atoi(&c);

      tmp += digitToChar(encryptedDigit);

      //debug
      dbugStr1 += intToString(n);
      dbugStr2 += intToString(encryptedDigit);
    }

  debug("message encrypted. "+msg+" > "+dbugStr1+" > "+dbugStr2+" > " + tmp);
  return tmp;
}

//decrypt
//encrypted message -> literal digits
//literal digits -> decrypted digits
//decrypted digits -> decrypted message
string decryptMessage(string msg)
{
  string tmp;
  string dbugStr1;
  string dbugStr2;
  for(int i = 0; i < msg.length(); i++)
    {
      const char c = randNumStr.at(i);
      int n = charToDigit(msg[i]);
      int decryptedDigit = n - atoi(&c); 

      //assure digit in letter range
      if(decryptedDigit < 0)
	{
	  decryptedDigit += length;
	}

      tmp += digitToChar(decryptedDigit);

      //debug
      dbugStr1 += intToString(n);
      dbugStr2 += intToString(decryptedDigit);
    }
  
  debug("message decrypted. "+msg+" > "+dbugStr1+" > "+dbugStr2+" > " + tmp);
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

//int -> string
string intToString(int n)
{
  ostringstream convert;
  convert << n;
  return convert.str();
}

void debug(string msg)
{
  cout << "DEBUG: " << msg << endl;
}
