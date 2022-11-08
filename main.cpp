#include "webserv.hpp"
#include "Parser.hpp"
#include <iostream>
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "INVALID ARGUMENTS\n";
    return (1);
  }
  else
  {
    ConfParser temp;
    std::string FilePath = argv[1];
    temp.parsing(FilePath);
    temp.displayAll();
  }
  return (0);
}