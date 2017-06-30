/*
 * Class Owner: Yichen Duan
 * This is the basic Hashnode template class that works for the HashTable template class
 * It contains fields of the template type K and V which contains the pages and tehir corresponding frequency,
 * one itself pointer next
 * It contains basic constructor, destructor, getters, and setters
 * Several methods related to TF/IDF calculation
 *
 * Changing history see the GitHub
 * */

#ifndef HASHNODE_H
#define HASHNODE_H
#include <math.h>
#include <iostream>
template <typename K, typename V>
class hashnode
{
private:
	K key;
	V value;

    hashnode *next;

    /*
     * @author Yichen Duan
     * @param max_t This is total number of words in a single page.
     *
     */
    double get_TF(long& max_t)
    {
        double temp = (0.5 + 0.5*value / max_t);
        return temp;
    }

    double get_IDF(long& totalPageNumber, long& pageNumberTermAppear)
    {
        double jaid = (double)totalPageNumber / (1 + (double)pageNumberTermAppear);
        double temp = log(jaid);
        return temp;
    }

public:
    hashnode():key(0),value(0),next(nullptr){}
    hashnode(const K &key):key(key), value(0), next(nullptr){}
    hashnode(K &key):key(key), value(0), next(nullptr){}
    hashnode(K &key, V &value):key(key),value(value), next(nullptr){}
    hashnode(const hashnode& hashN)
    {
        key = hashN.key;
        value = hashN.value;
        next = nullptr;
    }

    double get_TFIDF(long& max_t, long& totalPageNumber, long pageNumberTermAppear)
    {
        double TFIDF = get_TF(max_t)*get_IDF(totalPageNumber, pageNumberTermAppear);
        return TFIDF;
    }

    K& getKey()
	{
		return key;
	}

    V& getValue()
	{
		return value;
	}

    void addValue()
    {
        value++;
    }
    void combinValue(int var)
    {
        value+=var;
    }

    void setValue(const V& value)
	{
        hashnode::value = value;
	}
    void setKey(const V& key)
    {
        hashnode::key = key;
    }
    hashnode*& getNext()
	{
		return next;
	}

    void setNext(hashnode*& next)
	{
        hashnode::next = next;
	}
    //friend class hashtable;
};

#endif
