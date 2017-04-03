#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void createLetterMatrix();
void createRandomNumberString();
void encrypt(string msg);
char digitToChar(int n);
int charToDigit(char c);
int charToSingleDigit(char c);
void log(string msg);

const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char **letterMatrix = new char*[10];
string randNumStr;
vector<int> randNumVec;
string encryptStr;

int main()
{
  createLetterMatrix();
  createRandomNumberString();

  cout << "enter cipher message: "<< endl;
  string msg;
  cin >> msg;

  encrypt(msg);
  
  return 0;
}

void createLetterMatrix()
{
  //letters -> letter matrix
  letterMatrix[0] = new char[10];
  int a = 0;
  int b = 0;
  
  for(int i = 0; i < (sizeof letters)-1; i++)
    {
      letterMatrix[a][b] = letters[i];
      
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

  log("letter matrix created");
}

void createRandomNumberString()
{
  string hexStr;
  string numStr;
  string::iterator it;
  ifstream infile("random.hex");
  
  //check file access
  if(infile.is_open())
    {
      //file content -> string
      getline(infile, hexStr);
     
      //iterate string
      //hex char -> number
      //number -> 2nd string
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
      for(int i = 0; i < hexStr.length(); i++)
	{
	  stringstream ss;
	  ostringstream oss;
	  int tmp;
	  char c = hexStr[i];
	  ss << c;
	  ss >> hex >> tmp;
	  randNumVec.push_back(tmp);
	}
      
      infile.close();
      
      log("random number string created");
    }
  else
    {
      log("cant open file");
    }
}

void encrypt(string msg)
{
  //message -> literal digits
  string::iterator it;
  //string numMsg;
  int size = msg.length();
  int numMsgArr[size];
  vector<int> numMsgVec(size);
  
  for(int i = 0; i < msg.length(); i++)
    {
      ostringstream oss;
      char c = msg[i];
      int n = charToDigit(c);//charToSingleDigit(c);
      //oss << i;
      //numMsg += oss.str();
      numMsgArr[i] = n;
      numMsgVec[i] = n;
    }

  //literal digits -> encrypted digits
  vector<int> encryptNumMsgVec(size);
  for(int i = 0; i < size; i++)
    {
      encryptNumMsgVec[i] = numMsgVec[i] + randNumVec[i];
    }

  //encrypted digits -> encrypted message
  char c = digitToChar(30);
  cout << "c: " <<c;
}

//digit -> char
char digitToChar(int n)
{
  //assure digit in letter range
  while(n >= (sizeof letters))
    {
      n -= (sizeof letters)-1;
    }

  return letters[n];
}

//char -> digit
int charToDigit(char c)
{
  for(int i = 0; i < (sizeof letters)-1; i++)
    {
      if(c == letters[i])
	{
	  return i+1;
	}
    }

  log("no match found letter");
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
  
  log("no match found letter matrix");
  return -1;
}

void log(string msg)
{
  cout << "DEBUG: " << msg << '\n';
}
