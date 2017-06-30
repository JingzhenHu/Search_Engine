/* @author Jingzhen Hu
 * Class Owner: Jingzhen Hu
 * This is a class to deal with the queryer, it has two constructors: one deals with the single word(could combin with not)
 * The other deals with the logic combination (and, or, not). It will first be splits into a vector of words and a vector of exception
 * The words set is used for combination and/or while the except set is used for removing.
 * Then, it will eliminate stop words, turn each word into lowercase, and stemming.
 * Finally, it will pass out a hashtable<long,int> to RandAndSort class
 *
 * Changing history see the GitHub
 * */

#ifndef QUERYPARSER_H
#define QUERYPARSER_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>
//#include <unordered_map>
#include <fstream>
#include "porter2_stemmer.h"
#include "avltree.h"
#include <algorithm>
#include "hashtable.h"
#include "exavltree.h"
#include "rankandsort.h"
#include "indexinterface.h"
using std::string;
using std::vector;
class QueryParser
{
private:
    bool hasAND;
    bool hasOR;
    bool hasNOT;
    vector<string> words;
    vector<string> except;
    std::unordered_set<string> stopwords;
    hashtable<long, int> results;
    void middleProcess(string&, vector<string>&);
    void prepareField(vector<string>&);
    void eliminateStop(vector<string>&, istringstream&);
    void stemming(vector<string>&);
    void clearSpecialChars(std::string &);
public:
    QueryParser(IndexInterface*&, string, int, EXAVLTree<long>&, long&);
    QueryParser(IndexInterface*&, string&, string&, EXAVLTree<long>&, long&);

};

#endif // QUERYPARSER_H
