#include <map>
#include <vector>
#include <string>
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
    ParserNode rootnode;
public:
    CommonParser()
    {
        rootnode.next = NULL;
        rootnode.prev = NULL;
    }
    bool IsNodeElemEmpty(ParserNode node);
    ParserNode* GetNextNode(ParserNode node);
    std::vector<std::string> GetNodeElem(std::string key);
    void displayAll();
};

class ConfParser : public CommonParser
{
private:
    void getElem(ParserNode* temp, std::string line);
    ParserNode* EnterNode(ParserNode* temp, std::string line);
    ParserNode* exitNode(ParserNode* temp, std::string prevCategoly);

public:
    bool vaildCheck(std::string FileRoot);
    void parsing(std::string FileRoot);
};
