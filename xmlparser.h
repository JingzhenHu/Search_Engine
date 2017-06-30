/* @
 * Class Owner: Yichen Duan
 * This is a class for parsing, first using the RapidXML parser to store the title, text string
 * pageid and other information. Then dealing with them (spliting, removing special chars, stopwords, stemming)
 * Finally, insert them in the choosen index data strcuture.
 *
 * Changing history see the GitHub
 * */
#ifndef XMLPARSER_H
#define XMLPARSER_H
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "avltree.h"
#include "exavltree.h"
#include "indexhashtable.h"
#include "indexinterface.h"
#include "indexpersistence.h"
#include "porter2_stemmer.h"
typedef rapidxml::xml_node<> rapNode;
typedef rapidxml::xml_attribute<> attribute_type;
using namespace rapidxml;
using std::fstream;
using std::vector;
using std::string;

class XMLParser
{
private:
    char* xmlName;
    std::string title;
    std::string text;
    std::string timestamp;
    std::string contributor;
    rapidxml::xml_document<> doc;
    long id;
    long pageNum;
    long wordsForEachPage;
    std::unordered_set<string> stopwords;
    std::unordered_map<string, string> stem;
    //AVLTree<string> index;
    EXAVLTree<long> IDTree;
    IndexInterface* index;
    /*
     *
     * */
    rapNode* get_child(rapNode*, std::string);
    void eliminateStop(vector<string>&, istringstream&);
    void stemming(vector<string>&, vector<string>&);
    void clearSpecialChars(std::string &);

public:
    XMLParser(int);
    void readXML(char*);
    //AVLTree<string>& getIndex();
    IndexInterface*& getIndex();
    EXAVLTree<long>& getIDTree();
    long& getPageNum();
    ~XMLParser();
};

#endif // XMLPARSER_H
