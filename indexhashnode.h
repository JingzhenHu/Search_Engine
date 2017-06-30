/*
 * Class Owner: Yichen Duan
 * This is the basic indexHashNode template class that works for the IndexHashTable template class
 * It contains fields of the template type K's data, a object of hashtable<long,int>
 * which contains the pages and tehir corresponding frequency, a itself pointer ponits to next
 * It contains basic constructor, destructor, getters, and setters.
 *
 * Changing history see the GitHub
 * */

#ifndef INDEXHashNode_H
#define INDEXHashNode_H
#include <math.h>
#include <iostream>
#include "hashtable.h"
template <typename K>
class IndexHashNode
{
private:
    K key;
    hashtable<long,int> refs;
    IndexHashNode *next;

public:
    IndexHashNode():key(0),next(nullptr){}
    //IndexHashNode(const K &key):key(key), value(0), next(nullptr){}
    IndexHashNode(K &key, long& page):key(key), next(nullptr)
    {
        refs.put(page);
    }

    K& getKey()
    {
        return key;
    }

    hashtable<long,int>& getRefs()
    {
        return refs;
    }

    void setRefs(long& page, int& freq)
    {
        IndexHashNode::refs.put(page, freq);
    }

    void addRefs(long& page)
    {
        IndexHashNode::refs.put(page);
    }

    void setKey(const K& key)
    {
        IndexHashNode::key = key;
    }

    IndexHashNode*& getNext()
    {
        return next;
    }

    void setNext(IndexHashNode*& next)
    {
        IndexHashNode::next = next;
    }
    //friend class hashtable;
};

#endif // INDEXHashNode_H
