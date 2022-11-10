#include "Parser.hpp"
#include <cctype>
//CommonParser
bool CommonParser::IsNodeElemEmpty(ParserNode node)
{
    if (node.elem.size() == 0)
        return true;
    return false;
}

ParserNode* CommonParser::GetNextNode(ParserNode node)
{
    return (node.next);
}
/*
std::vector<std::string> CommonParser::GetNodeElem(std::string key)
{
    ParserNode *temp = NULL;
    std::map<std::string, std::vector<std::string> >::iterator it;

    temp = rootnode.next;
    it = rootnode.elem.end();
    while (temp)
    {
        it = temp->elem.find(key);
        if (it == temp->elem.end())
            temp = temp->next;
        else
            break;
    }
    return it->second;
}*/

void CommonParser::displayAll()
{
    for (unsigned int i = 0; i < nodevector.size(); ++i)
    {
        ParserNode *temp = &nodevector[i];
        while (temp)
        {
            std::cout << temp->categoly << std::endl;
            for (std::map<std::string, std::vector<std::string> >::iterator it = temp->elem.begin(); \
                it != temp->elem.end(); ++it)
            {
                std::cout << "  "<<it->first << " : ";
                for (unsigned long i = 0; i < it->second.size(); ++i)
                {
                    std::cout << it->second[i] << " ";
                }
                std::cout << std::endl;
            }
            temp = temp->next;
        }
    }
}

//ConfParser
bool ConfParser::vaildCheck(std::string FileRoot)
{
    std::stack<char> checkStack;
    std::filebuf fb;
    char getChar;

    if (fb.open(FileRoot, std::ios::in) == NULL)
        return false;
    std::istream is(&fb);
    while (is)
    {
        getChar = static_cast<char>(is.get());
        if (getChar == '{')
            checkStack.push(getChar);
        else if (getChar == '}')
        {
            if (checkStack.top() == '{')
                checkStack.pop();
            else
                checkStack.push(getChar);
        }
    }
    fb.close();
    if (checkStack.empty())
        return (true);
    return false;
}
// private
void ConfParser::getElem(ParserNode* temp, std::string line)
{
    std::string key;
    std::string buffer;
    std::vector<std::string> value;

    for (std::string::iterator it = line.begin(); it != line.end(); ++it)
    {
        if (isblank(*it) || *it == ';')
        {
            if (!key.empty() && !buffer.empty())
            {
                value.push_back(buffer);
                buffer.clear();
            }
            continue;
        }
        if (*it == ':' && key.size() == 0)
        {
            key = buffer;
            buffer.clear();
        }
        else
            buffer += *it;
    }
    temp->elem[key] = value;
}

ParserNode* ConfParser::EnterNode(ParserNode* temp, std::string line)
{
    while (temp->next)
        temp = temp->next;
    temp->next = new ParserNode;
    temp->next->prev = temp;
    temp->next->next = NULL;
    temp = temp->next;
    for (std::string::iterator it = line.begin(); it != line.end(); ++it)
    {
        if (isblank(*it) || *it == '{')
            continue;
        temp->categoly += *it;
    }
    return temp;
}

CommonParser::~CommonParser()
{
    ParserNode *origin;
    ParserNode *temp;

    for (unsigned int i = 0; i < nodevector.size(); ++i)
    {
        origin = nodevector[i].next;
        while (origin)
        {
            temp = origin->next;
            delete origin;
            origin = temp;
        }
    }
}

void ConfParser::parsingOneNode(std::istream& is)
{
    std::string buffer;
    ParserNode rootnode;
    ParserNode *temp = &rootnode;

    rootnode.next = NULL;
    rootnode.prev = NULL;
    while (!getline(is, buffer).eof())
    {
        if (buffer.size() == 0)
            continue;
        if (*buffer.rbegin() == ';')
            getElem(temp, buffer);
        else if(*buffer.rbegin() == '{')
            temp = EnterNode(temp, buffer);
        else if(*buffer.rbegin() == '}')
        {
            if (temp == rootnode.next)
                break;
            temp = rootnode.next;
        }
        buffer.clear();
    }
    if (rootnode.next)
        nodevector.push_back(rootnode);
}

void ConfParser::parsing(std::string FileRoot)
{
    std::filebuf fb;

    if (fb.open(FileRoot, std::ios::in) == NULL)
        return;
    std::istream is(&fb);
    while (is)
        parsingOneNode(is);
    fb.close();
}
//RequestParser

//private
void RequestParser::parsingOneNode(std::istream& is)
{
    std::string buffer;
    ParserNode rootnode;
    ParserNode *temp = &rootnode;

    rootnode.next = NULL;
    rootnode.prev = NULL;
    while (!getline(is, buffer).eof())
    {
        if (buffer.size() == 0)
            continue;
        if (*buffer.rbegin() == ';')
            getElem(temp, buffer);
        else if(*buffer.rbegin() == '{')
            temp = EnterNode(temp, buffer);
        else if(*buffer.rbegin() == '}')
        {
            if (temp == rootnode.next)
                break;
            temp = rootnode.next;
        }
        buffer.clear();
    }
    if (rootnode.next)
        nodevector.push_back(rootnode);
}

//public
void RequestParser::parsing(std::string FileRoot)
{
    std::filebuf fb;

    if (fb.open(FileRoot, std::ios::in) == NULL)
        return;
    std::istream is(&fb);
    while (is)
        parsingOneNode(is);
    fb.close();
}