#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>

void init();
std::string createRandomNumberString();
int charTo1dig(char c);

char **letterMatrix = new char*[10];
std::string randNumStr;

int main()
{
  init();
  randNumStr = createRandomNumberString();
    
  return 0;
}

void init()
{
  //letters -> letter matrix
  const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  letterMatrix[0] = new char[10];
  int a = 0;
  int b = 0;
  
  for(int i = 0; i < (sizeof letters)-1; i++)
    {
      letterMatrix[a][b] = letters[i];

      std::cout << letterMatrix[a][b];//debug
      std::cout << ", a: " << a << ", b: " << b << std::endl;//debug
      
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
}

std::string createRandomNumberString()
{
  std::string hexStr;
  std::string numStr;
  std::string::iterator it;
  std::ifstream infile("random.hex");
  
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
	    std::stringstream ss;
	    char val = *it;
	   
	    ss << val;
	    ss >> std::hex >> tmp;
	    std::ostringstream con;
	    con << tmp;
	    numStr += con.str();
	}
      
      infile.close();
      
      //debug
      std::cout << hexStr << '\n';
      std::cout << numStr << '\n';

      return numStr;
    }
  else
    {
      std::cout << "cant open file";

      return "";
    }
}

int charTo1dig(char c)
{
 
}
