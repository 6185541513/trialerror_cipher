#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>

void init();
int charTo1dig(char c);

int main()
{
  std::string hexStr;
  std::string numStr;
  std::string::iterator it;
  std::ifstream infile("random.hex");
  
  //check file access
  if(infile.is_open())
    {
      //       init();
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
      init();
      //print strings
      std::cout << hexStr << '\n';
      std::cout << numStr << '\n';
      
      infile.close();
    }
  else
    {
      std::cout << "cant open file";
    }
    
  return 0;
}

void init()
{
  const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  // char convertedLetters[26];
  char **letterMatrix = (char **) new char*[10];
  int a = 0;
  int b = 0;
  
  for(int i = 0; i < (sizeof letters)-1; i++)
    {
      letterMatrix[a][b] = letters[i];

      std::cout << letterMatrix[a][b];
      std::cout << ", a: " << a << ", b: " << b << std::endl;
      
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

int charTo1dig(char c)
{
  const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  // char []convertedLetters;
  char **letterMatrix = (char **) new char*[10];
  int a = 0;
  int b = 0;
  
  for(int i = 0; i < (sizeof letters)-1; i++)
    {
      letterMatrix[a][b] = letters[i];

      std::cout << letterMatrix[a][b];
      std::cout << ", a: " << a << ", b: " << b << std::endl;
      
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
