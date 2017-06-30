/*
 * Class Owner: Yichen Duan
 * This class is the HashTable container for index. It has the basic fields of an array of
 * HashNode pointers, and each hashnode pointer points to a linkedlist.
 *
 * It has a basic hash function, insert, remove, isEmpty, ifExist, and print functions.
 * The write_XML function works for the indexpersistence in order to write a xmlfile in disk
 *
 * Changing history see the GitHub
 * */

#ifndef INDEXHashTable_H
#define INDEXHashTable_H
#include "indexhashnode.h"
#include "indexinterface.h"
#include <iostream>
#include <string>
#include <cstring>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace rapidxml;
using namespace std;

template <typename K>
class IndexHashTable : public IndexInterface
{
private:
    IndexHashNode<K> **table;
    const long TABLE_SIZE = 200000;
public:
    IndexHashTable()
    {
        table = new IndexHashNode<K> *[TABLE_SIZE]();
    }

    long getTotalNode()
    {
        long ctr = 0;
        for (long i = 0; i < TABLE_SIZE; i++)
        {
            IndexHashNode<K>* node = table[i];
            while (node)
            {
                ctr++;
                node = node->getNext();
            }
        }
        return ctr;
    }


    void writeInOrder(IndexHashNode<K>*& ptr, xml_document<>*& doc, xml_node<>*& files)
    {
        if(ptr == nullptr)
            return;
        else
        {
            xml_node<> *words = doc->allocate_node(node_element, "word");
            files->append_node(words);
            xml_node<> *name = doc->allocate_node(node_element, "name", ptr->getKey().c_str());
            words->append_node(name);
            xml_node<> *value_pair = doc->allocate_node(node_element, "valuepair");
            words->append_node(value_pair);
            ptr->getRefs().writeXML(doc, value_pair);
            writeInOrder(ptr->getNext(), doc, files);
        }
    }

    void writeXML()
    {
        xml_document<>* doc = new xml_document<>;
        xml_node<> *files = doc->allocate_node(node_element, "root");
        doc->append_node(files);
        IndexHashNode<K> *curNode = table[0];
        for(int i = 0; i < TABLE_SIZE; i++)
        {
            curNode = table[i];
            writeInOrder(curNode, doc, files);
        }
        std::ofstream myfile;
        myfile.open("WordHashTable.xml");
        myfile << *doc;
        myfile.close();
    }

    size_t& hash(K& key)
    {
        std::hash<K> hash_fn;
        size_t str_hash = hash_fn(key)%TABLE_SIZE;
        return str_hash;
    }

    hashtable<long,int> get(K& key)
    {
        const unsigned long hashValue = hash(key);
        IndexHashNode<K> *curNode = table[hashValue];

        while (curNode != nullptr)
        {
            if (curNode->getKey() == key)
            {
                return curNode->getRefs();
            }
            curNode = curNode->getNext();
        }
    }
/*
    IndexHashNode<K>**& getTableNode()
    {
        return table;
    }*/

    bool isEmpty()
    {
        for(int i = 0; i < TABLE_SIZE; i++)
        {
            if(table[i] != nullptr)
            {
                return false;
            }
        }
        return true;
    }

    bool find(K& key)
    {
        unsigned long hashValue = hash(key);
        IndexHashNode<K> *curNode = table[hashValue];

        while (curNode != nullptr)
        {
            if (curNode->getKey() == key)
            {
                //value = curNode->getValue();
                return true;
            }
            curNode = curNode->getNext();
        }
        return false;
    }


    void print()
    {
        IndexHashNode<K> *curNode = table[0];
        for(int i = 0; i < TABLE_SIZE; i++)
        {
            curNode = table[i];
            printTableList(curNode);
        }
    }

    void printTableList(IndexHashNode<K>*& ptr)
    {
        if(ptr == nullptr)
            return;
        else
        {
            printTableList(ptr->getNext());
            std::cout<< ptr->getKey()<<": "<< std::endl;
            ptr->getRefs().printTable();
        }
    }

    void insert(K& key, long& page)
    {
        unsigned long hashValue = hash(key);
        IndexHashNode<K> *prev = nullptr;
        IndexHashNode<K> *curNode = table[hashValue];

        while (curNode != nullptr && curNode->getKey() != key)
        {
            prev = curNode;
            curNode = curNode->getNext();
        }

        if (curNode == nullptr)
        {
            curNode = new IndexHashNode<K>(key, page);
            if (prev == nullptr)
            {
                table[hashValue] = curNode;
            }
            else
            {
                prev->setNext(curNode);
            }
        }
        else
        {
            curNode->addRefs(page);
        }
    }

    void delete_all()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            IndexHashNode<K> *curNode = table[i];
            while (curNode != nullptr)
            {
                IndexHashNode<K> *prev = curNode;
                curNode = curNode->getNext();
                delete prev;
            }
            table[i] = nullptr;
        }
        delete[] table;
    }

    ~IndexHashTable()
    {
        delete_all();
    }
};

#endif // INDEXHashTable_H
