/*
 * Class Owner: Yichen Duan
 * This is a class for persistence of index. It can write out the xml file in disk based
 * on the IDTree and index passed in. It also can shows some statistcs and read.
 *
 * Changing history see the GitHub
 * */

#ifndef INDEXPERSISTENCE_H
#define INDEXPERSISTENCE_H
#include <iostream>
#include <fstream>
#include "indexinterface.h"
#include "avltree.h"
#include "exavltree.h"
#include "hashtable.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace rapidxml;

class IndexPersistence
{
private:
    EXAVLTree<long> IDTree;
    IndexInterface* WordTree;
    void write_IDTree_XML(EXAVLTree<long>&);
    void write_WordTree_XML(IndexInterface*&);

public:
    IndexPersistence();
    EXAVLTree<long>& getIDTree();
    IndexInterface*& getWordTree();
    void printStatisticData(EXAVLTree<long>&, IndexInterface*&);
    void write_XML(EXAVLTree<long>&, IndexInterface*&);
    ~IndexPersistence();
};

#endif // INDEXPERSISTENCE_H
