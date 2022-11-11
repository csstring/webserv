#include "webserv.hpp"
#include "Parser.hpp"
#include <iostream>

void main3(char *argv[])
{
    RequestParser temp;
    std::string key;
    std::string category;
    std::vector<std::string> val;
    std::string FilePath = argv[1];
    temp.parsing(FilePath);
    temp.displayAll();
    while (1)
    {
      std::cout << "enter key : " << "<<"<< std::endl;
      getline(std::cin, key);
      std::cout << "enter cateogory : " << "<<" << std::endl;
      getline(std::cin, category);
      val = temp.GetNodeElem(category, key);
      for (unsigned int i = 0; i < val.size(); ++i)
      {
        std::cout << "categoly : " << category << std::endl;
        std::cout << "key : " << key << std::endl;
        std::cout << "val : " << val[i] << std::endl;
      }
      val.clear();
    }
}

void main2(char *argv[])
{
    ConfParser temp;
    std::string FilePath = argv[1];
    ConfParser::vaildCheck(FilePath);
    temp.parsing(FilePath);
    temp.displayAll();
    std::string key;
    std::string category;
    std::vector<std::string> val;
    std::string server_index;

    while (1)
    {
      std::cout << "enter cateogory : " << "<<" << std::endl;
      getline(std::cin, category);
      std::cout << "enter key : " << "<<"<< std::endl;
      getline(std::cin, key);
      std::cout << "enter server_index : " << "<<" << std::endl;
      getline(std::cin, server_index);
      val = temp.GetNodeElem(std::stoi(server_index) , category, key);
      for (unsigned int i = 0; i < val.size(); ++i)
      {
        std::cout << "categoly : " << category << std::endl;
        std::cout << "key : " << key << std::endl;
        std::cout << "val : " << val[i] << std::endl;
      }
      val.clear();
    }
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "INVALID ARGUMENTS\n";
    return (1);
  }
  else
  {
    main2(argv);
    system("leaks webserv");
  }
  return (0);
}