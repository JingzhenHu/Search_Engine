#include "xmlparser.h"

XMLParser::XMLParser(int container)
{
    pageNum = 0;
    if (container == 1)
    {
        index = new AVLTree<string>;
    }
    else if(container == 2)
    {
        index = new IndexHashTable<string>;
    }
    fstream file;
    file.open("StopWord.txt");
    if(file.is_open())
    {
        while(!file.eof())
        {
            std::string eachWord;
            std::getline(file,eachWord);
            stopwords.insert(eachWord);
        }
        file.close();
    }
}

void XMLParser::readXML(char* fileName)
{
    xmlName = new char[strlen(fileName)+1];
    strcpy(xmlName, fileName);
    std::string buffer = "";
    rapidxml::file<> xmlFile(xmlName); // Default template is char
    std::cout << "Good! Please wait\n";
    doc.parse<0>(xmlFile.data());
    rapNode* curNode = doc.first_node();
    curNode = get_child(curNode, "page");
    //std::cout<<"get "<<curNode->name()<<"\n";
    rapNode* temp = curNode;
    while(curNode!=0)
    {
        curNode = get_child(temp, "title");
        title = curNode->value();
        string title_origin = title;
        curNode = get_child(temp, "id");     
        //std::cout<<id<<"\n";
        buffer = curNode->value();
        id = stol(buffer);

        curNode = get_child(temp, "revision");
        curNode = get_child(curNode, "timestamp");
        if(curNode != nullptr)
        {
            timestamp = curNode->value();
        }

        curNode = get_child(temp, "revision");
        curNode = get_child(curNode, "contributor");
        curNode = get_child(curNode, "username");
        if(curNode!=nullptr)
        {
            contributor = curNode->value();
        }

        curNode = get_child(temp, "revision");
        curNode = get_child(curNode, "text");
        text = curNode->value();
        string text_origin = text;

        clearSpecialChars(text);
        clearSpecialChars(title);
        std::transform(text.begin(), text.end(), text.begin(), ::tolower);
        std::transform(title.begin(), title.end(), title.begin(), ::tolower);
        std::istringstream stp (title);
        std::vector<std::string> title_vec;
        eliminateStop(title_vec, stp);
        std::istringstream stq (text);
        std::vector<std::string> text_vec;
        eliminateStop(text_vec, stq);
        IDTree.insert(id, wordsForEachPage, title_origin, text_origin, timestamp, contributor);
        stemming(title_vec, text_vec);
        for(int i = 0; i < text_vec.size(); i++)
            index->insert(text_vec[i], id);
        for(int i = 0; i < title_vec.size(); i++)
            index->insert(title_vec[i], id);
        curNode = temp->next_sibling();
        temp = curNode;
        pageNum++;
    }
}

rapNode* XMLParser::get_child(rapNode *inputNode, std::string sNodeFilter)
{
    // cycles every child
    for (rapNode *nodeChild = inputNode->first_node(); nodeChild; nodeChild = nodeChild->next_sibling())
    {
        if (nodeChild->name() == sNodeFilter)
        {
            // returns the desired child
            return nodeChild;
        }
        rapNode * x = get_child(nodeChild, sNodeFilter);
        if (x)
          return x;
    }
    return 0;
}


void XMLParser::clearSpecialChars(std::string &word)
{
    int i = 0;
    for (string::iterator it = word.begin(); it < word.end(); it++, i++)
    {
        if (!isalpha(word[i]))
        {
            word[i] = ' ';
        }
    }
}


void XMLParser::eliminateStop(vector<string>& vector, istringstream& word)
{
    wordsForEachPage = 0;
    std::string buffer = "";
    while(!word.eof())
    {
        word>>buffer;
        if(stopwords.find(buffer) == stopwords.end())
        {
            vector.push_back(buffer);
            wordsForEachPage++;
        }
    }
}

void XMLParser::stemming(vector<string>& title_vec, vector<string>& text_vec)
{
    string to_stem;
    for(int i = 0; i < title_vec.size(); i++)
    {
        to_stem = title_vec[i];
        std::unordered_map<std::string,string>::const_iterator got = stem.find (to_stem);
        if(got == stem.end())
        {
            Porter2Stemmer::stem(title_vec[i]);
            stem[to_stem] = title_vec[i];
        }
        else
            title_vec[i] = got->second;
    }
    for(int i = 0; i < text_vec.size(); i++)
    {
        to_stem = text_vec[i];
        std::unordered_map<std::string,string>::const_iterator got = stem.find (to_stem);
        if(got == stem.end())
        {
            Porter2Stemmer::stem(text_vec[i]);
            stem[to_stem] = text_vec[i];
        }
        else
            text_vec[i] = got->second;
    }
}


IndexInterface*& XMLParser::getIndex()
{
    return index;
}

EXAVLTree<long>& XMLParser::getIDTree()
{
    return IDTree;
}

long& XMLParser::getPageNum()
{
    return pageNum;
}

XMLParser::~XMLParser()
{
    if(index!= nullptr)
    {
        //index->delete_all();
    }
}
