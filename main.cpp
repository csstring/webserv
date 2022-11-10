#include "webserv.hpp"
#include "Parser.hpp"
#include <iostream>

void main2(char *argv[])
{
    ConfParser temp;
    std::string FilePath = argv[1];
    ConfParser::vaildCheck(FilePath);
    temp.parsing(FilePath);
    temp.displayAll();
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