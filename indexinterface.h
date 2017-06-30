/* @author Jingzhen Hu
 * Class Owner: Jingzhen Hu
 * This is a simple pure abstract class (like a interface) to make use of
 * either avltree index structure or hashtable index structure
 *
 * It contains the common funtions insert(add word), delete_all(clear),
 * find(search based on the word), get(the pages and freqs), write_XML(store out),
 * print(test for programming), getTotalNode(get the amount of words in the index)
 * */

#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <string>
#include "hashtable.h"
using namespace std;
class IndexInterface
{
public:
    /*add word into the index*/
    virtual void insert(string&, long&) = 0;
    /*clear all data in the index*/
    virtual void delete_all() = 0;
    /*judge wether the certain data is in the index or not*/
    virtual bool find(string& ) = 0;
    /*get the pages and frequencies based on the certain word*/
    virtual hashtable<long,int> get(string& data) = 0;
    /*write the whole index out in the disk*/
    virtual void writeXML() = 0;
    /*print is a test for programming*/
    virtual void print() = 0;
    /*return the total words in each index*/
    virtual long getTotalNode() = 0;
};
#endif // INDEXINTERFACE_H
