#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <exception>

struct ParserNode
{
    ParserNode *next;
    ParserNode *prev;
    std::string categoly;
    std::map<std::string, std::vector<std::string> > elem;
};

class CommonParser
{
protected:
    std::vector<ParserNode> nodevector;
public:
    bool IsNodeElemEmpty(ParserNode node);
    ParserNode* GetNextNode(ParserNode node);
//  std::vector<std::string> GetNodeElem(std::string key);
    ~CommonParser();
    void displayAll();
};

class ConfParser : public CommonParser
{
private:
    void getElem(ParserNode* temp, std::string line);
    ParserNode* EnterNode(ParserNode* temp, std::string line);
    void parsingOneNode(std::istream& is);
public:
    static bool vaildCheck(std::string FileRoot);
    void parsing(std::string FileRoot);
};

class RequestParser : public CommonParser
{
private:
    void getElem(ParserNode* temp, std::string line);
    ParserNode* EnterNode(ParserNode* temp, std::string line);
    void parsingOneNode(std::istream& is);
public:
    void parsing(std::string FileRoot);
};