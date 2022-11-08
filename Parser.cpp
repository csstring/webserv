#include "Parser.hpp"
#include <stack>
#include <iostream>
#include <fstream>
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
}

void CommonParser::displayAll()
{
    ParserNode *temp = &rootnode;
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
        if (*it == ':')
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
ParserNode* ConfParser::exitNode(ParserNode* temp, std::string prevCategoly)
{
    while (temp->prev)
    {
        temp = temp->prev;
        if (temp->categoly == prevCategoly)
            break;
    }
    return temp;
}

void ConfParser::parsing(std::string FileRoot)
{
    std::filebuf fb;
    std::string buffer;
    ParserNode *temp = &this->rootnode;
    std::string prevCategoly;

    if (fb.open(FileRoot, std::ios::in) == NULL)
        return;
    std::istream is(&fb);
    while (is)
    {
        getline(is, buffer);
        if (buffer.size() == 0)
            continue;
        if (*buffer.rbegin() == ';')
            getElem(temp, buffer);
        else if(*buffer.rbegin() == '{')
        {
            prevCategoly = temp->categoly;
            temp = EnterNode(temp, buffer);
        }
        else if(*buffer.rbegin() == '}')
            temp = exitNode(temp, prevCategoly);
        buffer.clear();
    }
    fb.close();
}