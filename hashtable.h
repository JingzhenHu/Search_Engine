/* @author Jingzhen Hu
 * Class Owner: Jingzhen Hu
 * This class is the HashTable container for pages and frequencies. It has the basic fields of an array of
 * HashNode pointers, and each hashnode pointer points to a linkedlist. It has a copy constructor, and
 * a assginment operator, a destructor.
 * It has a basic hash function, insert, remove, isEmpty, ifExist, and print functions.
 * The writevaluepairs function works for the indexpersistence in order to write a xmlfile in disk
 * The combinAND, combinNOT, combinNOT, and putOR works for the queryerparser.
 * Besides, it also contains needed basic getters.
 *
 * Changing history see the GitHub
 * */

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "hashnode.h"
#include <iostream>
#include <string>
#include <cstring>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace rapidxml;
using namespace std;

template <typename K, typename V>
class hashtable
{
private:
    hashnode<K, V> **table;
    const long TABLE_SIZE = 2048;
public:
    /*constructor*/
    hashtable()
    {
        table = new hashnode<K, V> *[TABLE_SIZE]();
	}
    /*return the amount of page number that the sertain word appears*/
    long getDocNum()
    {
        long ctr = 0;
        for (long i = 0; i < TABLE_SIZE; i++)
        {
            hashnode<K, V>* node = table[i];
            while (node != nullptr)
            {
                ctr++;
                node = node->getNext();
            }
        }
        return ctr;
    }
    /* a simple hash function*/
	unsigned long hash(const long &key)
	{
		return key%TABLE_SIZE;
	}
    /*copy constructor*/
    hashtable(const hashtable& hashT)
    {
        table = new hashnode<K, V> *[TABLE_SIZE]();

        for (long i = 0; i < TABLE_SIZE; i++)
        {
            hashnode<K, V>* node = hashT.table[i];
            hashnode<K, V>** ptr = &table[i];
            *ptr = nullptr;
            while (node)
            {
                hashnode<K, V>* curNode = new hashnode<K, V>(*node);
                *ptr = curNode;
                ptr = &curNode->getNext();
                node = node->getNext();
            }
        }
    }
    /*assignment operator*/
    hashtable& operator= (const hashtable& hashT)
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            hashnode<K, V> *curNode = table[i];
            while (curNode != nullptr)
            {
                hashnode<K, V> *prev = curNode;
                curNode = curNode->getNext();
                delete prev;
            }
            table[i] = nullptr;
        }
        delete[] table;

        table = new hashnode<K, V> *[TABLE_SIZE]();

        for (long i = 0; i < TABLE_SIZE; i++)
        {
            hashnode<K, V>* node = hashT.table[i];
            hashnode<K, V>** ptr = &table[i];
            *ptr = nullptr;
            while (node)
            {
                hashnode<K, V>* curNode = new hashnode<K, V>(*node);
                *ptr = curNode;
                ptr = &curNode->getNext();
                node = node->getNext();
            }
        }
        return *this;
    }
    /* AND logic combination of two hashtable*/
    void combinAND(hashtable<K, V>& ref)
    {
        hashnode<K, V>* curNode;
        for(int i = 0; i < TABLE_SIZE; i++)
        {
            curNode = table[i];
            while(curNode!=nullptr)
            {
                if(ref.ifExist(curNode->getKey()))
                {
                    int freq = curNode->getValue() + ref.getValue(curNode->getKey());
                    curNode->setValue(freq);
                }
                else
                {
                    remove(curNode->getKey());
                }
                curNode = curNode->getNext();
            }
        }
    }
    /*get the freqency based on the certain page for certain word*/
    V& getValue(const K &key)
    {
        unsigned long hashValue = hash(key);
        hashnode<K, V> *curNode = table[hashValue];

        while (curNode != nullptr)
        {
            if (curNode->getKey() == key)
            {
                return curNode->getValue();
            }
            curNode = curNode->getNext();
        }
    }
    /*OR logic combination for two hashtable*/
    void combinOR(hashtable<K, V>& ref)
    {
        hashnode<K, V>* curNode;
        for(int i = 0; i < TABLE_SIZE; i++)
        {
            curNode = ref.getTableNode()[i];
            while(curNode!=nullptr)
            {
                int freq = curNode->getValue();
                putOR(curNode->getKey(), freq);
                curNode = curNode->getNext();
            }
        }
    }
    /* put function for the OR combination logicly*/
    void putOR(const K &key, int freq)
    {
        unsigned long hashValue = hash(key);
        hashnode<K, V> *prev = nullptr;
        hashnode<K, V> *curNode = table[hashValue];

        while (curNode != nullptr && curNode->getKey() != key)
        {
            prev = curNode;
            curNode = curNode->getNext();
        }

        if (curNode == nullptr)
        {
            curNode = new hashnode<K, V>();
            curNode->setKey(key);
            curNode->setValue(freq);
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
            curNode->combinValue(freq);
        }
    }
    /* NOT combination for two hashtable the paramter is the pages that are needed to remove*/
    void combinNOT(hashtable<K, V>& ref)
    {
        hashnode<K, V>* curNode;
        for(int i = 0; i < TABLE_SIZE; i++)
        {
            curNode = ref.getTableNode()[i];
            while(curNode!=nullptr)
            {
                if(ifExist(curNode->getKey()))
                    remove(curNode->getKey());
                curNode = curNode->getNext();
            }
        }
    }
    /*return the table: a pointer of a pointer hashnode*/
    hashnode<K, V>**& getTableNode()
    {
        return table;
    }
    /*judge whether the hashtable is empty or not*/
    bool isEmpty()
    {
        bool isEm = true;
        for(int i = 0; i < TABLE_SIZE; i++)
        {
            if(table[i] != nullptr)
            {
                isEm = false;
                break;
            }
        }
        return isEm;
    }
    /* check the pages is existed in the refs or not*/
    bool ifExist(const K &key)
	{
		unsigned long hashValue = hash(key);
        hashnode<K, V> *curNode = table[hashValue];

		while (curNode != nullptr)
		{
			if (curNode->getKey() == key)
            {
				return true;
			}
			curNode = curNode->getNext();
		}
		return false;
	}

    /*print the whole table*/
    void printTable()
    {
        hashnode<K, V> *curNode = table[0];
        for(int i = 0; i < TABLE_SIZE; i++)
        {
            curNode = table[i];
            printTableList(curNode);
        }
    }
    /*print function for each hashnode in the hashnode array*/
    void printTableList(hashnode<K, V>*& ptr)
    {
        if(ptr == nullptr)
            return;
        else
        {
            printTableList(ptr->getNext());
            std::cout<<" appears on page: "<<ptr->getKey()<<" with frequence: "<<ptr->getValue()<<"\n";
        }
    }
    /*put function is to add the page when the page does not existed, or add the frequency*/
    void put(const K &key)
    {
        unsigned long hashValue = hash(key);
        hashnode<K, V> *prev = nullptr;
        hashnode<K, V> *curNode = table[hashValue];

        while (curNode != nullptr && curNode->getKey() != key)
        {
            prev = curNode;
            curNode = curNode->getNext();
        }

        if (curNode == nullptr)
        {
            curNode = new hashnode<K, V>();
            curNode->setKey(key);
            curNode->addValue();
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
            curNode->addValue();
        }
    }
    /* This funcion works for read in the prcoessed xml file in disk*/
    void put(const K& key, const V& value)
    {
        unsigned long hashValue = hash(key);
        hashnode<K, V> *prev = nullptr;
        hashnode<K, V> *curNode = table[hashValue];

        while (curNode != nullptr && curNode->getKey() != key)
        {
            prev = curNode;
            curNode = curNode->getNext();
        }

        curNode = new hashnode<K, V>(key, value);
        if (prev == nullptr)
        {
            table[hashValue] = curNode;
        }
        else
        {
            prev->setNext(curNode);
        }

    }
    /*write the refs out in disk*/
    void writeXML(xml_document<>*& doc, xml_node<>*& valuepair)
    {
        hashnode<K, V> *curNode = table[0];
        for(int i = 0; i < TABLE_SIZE; i++)
        {
            curNode = table[i];
            writepairs(curNode, doc, valuepair);
        }
    }
    /*works for the wirteXML function*/
    void writepairs(hashnode<K, V>*& ptr, xml_document<>*& doc, xml_node<>*& valuepair)
    {
        if(ptr == nullptr)
            return;
        else
        {
            writepairs(ptr->getNext(), doc, valuepair);
            xml_node<> *pair = doc->allocate_node(node_element, "pair");
            valuepair->append_node(pair);
            string buffer = to_string(ptr->getKey());
            char* page = new char[buffer.length()+1];
            std::strcpy(page, buffer.c_str());
            xml_node<> *id = doc->allocate_node(node_element, "id", page);
            pair->append_node(id);
            buffer = to_string(ptr->getValue());
            char* frequency = new char[buffer.length()+1];
            std::strcpy(frequency, buffer.c_str());
            xml_node<> *freq = doc->allocate_node(node_element, "frequency", frequency);
            pair->append_node(freq);
        }
    }
    /* remove a certain hashnode in the hashtable*/
    void remove(const K &key)
	{
		unsigned long hashValue = hash(key);
        hashnode<K, V> *prev = nullptr;
        hashnode<K, V> *curNode = table[hashValue];

		while (curNode != nullptr && curNode->getKey() != key)
		{
			prev = curNode;
			curNode = curNode->getNext();
		}

		if (curNode == nullptr)
		{
			return;
		}
		else
		{
			if (prev == nullptr)
			{
				table[hashValue] = curNode->getNext();
			}
			else
			{
				prev->setNext(curNode->getNext());
			}
			delete curNode;
		}
	}
    /* destructor*/
    ~hashtable()
	{
		for (int i = 0; i < TABLE_SIZE; ++i)
		{
            hashnode<K, V> *curNode = table[i];
			while (curNode != nullptr)
			{
                hashnode<K, V> *prev = curNode;
				curNode = curNode->getNext();
				delete prev;
			}
			table[i] = nullptr;
		}
		delete[] table;
    }
    friend class RankAndSort;
};
#endif
