#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;

void createLetterMatrix();
void createRandomNumberString();
void encrypt(string msg);
void log(string msg);

char **letterMatrix = new char*[10];
string randNumStr;
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
  const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
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
	    int tmp;
	    stringstream ss;
	    char val = *it;
	   
	    ss << val;
	    ss >> hex >> tmp;
	    ostringstream con;
	    con << tmp;
	    randNumStr += con.str();
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
  
}

void log(string msg)
{
  cout << "DEBUG: " << msg << '\n';
}
