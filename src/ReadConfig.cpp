#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include <string>

struct ConfigureNode
{
  std::vector<std::string> elem;
  std::map<std::string, ConfigureNode> next;
};

std::string getDataFromFile(char *filePath)
{
  std::ifstream infileStream;
  std::ostringstream ss;

  infileStream.open(filePath);
  assert(infileStream.bad() == 0);
  ss << infileStream.rdbuf();
  return (ss.str());
}

void  parseConfigure(char *configFilePath)
{
  std::string fileData = getDataFromFile(configFilePath);
  std::string temp_line;
  std::map<std::string, ConfigureNode> server;
  std::stack<char> vaild_check;
/*
  for (std::string::iterator it = fileData.begin(); it != fileData.end(); it++)
  {

  }
*/
  server["server_name"].elem.push_back("test");
  std::cout << *(server.find("server_name")->second.elem.begin()) << std::endl;
  //std::cout << fileData;
}
