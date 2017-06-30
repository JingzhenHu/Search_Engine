/* @author Jingzhen Hu
 * Class Owner: Jingzhen Hu
 * This is the basic AVLnode template class that works for the AVLTree template class
 * It contains fields of the template type T's data, a object of hashtable<long,int>
 * which contains the pages and tehir corresponding frequency, a integer to represent height,
 * two itself pointers(right and left).
 * It contains basic constructor, destructor, getters, and setters.
 * It conatisn the addRefs, setRefs work seperately for the insert function in avltree and
 * retrieve from the xmlfile in disk.
 *
 * Changing history see the GitHub
 * */

#ifndef AVLNODE_H
#define AVLNODE_H
#include "hashtable.h"
using namespace std;
template <typename T>
class AVLNode
{
private:
    T data;
    int height;
    hashtable<long,int> refs;
    AVLNode<T>* left;
    AVLNode<T>* right;
public:
    AVLNode();
    AVLNode(T t);
    AVLNode(T t,long page);
    ~AVLNode();
    hashtable<long,int> getRefs();
    T& getData();
    const T& getConst() const;
    int& getHeight();
    AVLNode<T>*& getLeft();
    AVLNode<T>*& getRight();
    void addRefs(long& page);
    void setData(T& t);
    void setLeft(AVLNode<T>*& l);
    void setRight(AVLNode<T>*& r);
    void setHeight(int h);
    void setRefs(long& page,int& freq);
};
/*constructors*/
template <typename T>
AVLNode<T>::AVLNode():left(0),right(0),height(0){}
template <typename T>
AVLNode<T>::AVLNode(T t):data(t),left(0),right(0),height(0){}
template <typename T>
AVLNode<T>::AVLNode(T t,long page):data(t)
{
    refs.put(page);
    right = 0;
    left = 0;
    height = 0;
}
/*destrcuctor*/
template <typename T>
AVLNode<T>::~AVLNode()
{
    if(left != 0)
    {
        delete left;
        left = 0;
    }
    if(right!=0)
    {
        delete right;
        right = 0;
    }
}
/* getters and setters*/
template <typename T>
hashtable<long,int> AVLNode<T>::getRefs()
{
    return refs;
}


template <typename T>
T& AVLNode<T>::getData()
{
    return data;
}

template <typename T>
const T& AVLNode<T>::getConst() const
{
    return data;
}
template <typename T>
int& AVLNode<T>::getHeight()
{
    return height;
}
template <typename T>
AVLNode<T>*& AVLNode<T>::getLeft()
{
    return left;
}
template <typename T>
AVLNode<T>*& AVLNode<T>::getRight()
{
    return right;
}
/* for the same page, add frequency, if not, add the page*/
template <typename T>
void AVLNode<T>::addRefs(long& page)
{
    refs.put(page);
}
template <typename T>
void AVLNode<T>::setData(T& t)
{
    data = t;
}
template <typename T>
void AVLNode<T>::setLeft(AVLNode<T>*& l)
{
    left = l;
}
template <typename T>
void AVLNode<T>::setRight(AVLNode<T>*& r)
{
    right = r;
}
template <typename T>
void AVLNode<T>::setHeight(int h)
{
    height = h;
}
/*works for read in sml file in disk*/
template <typename T>
void AVLNode<T>::setRefs(long& page,int& freq)
{
    refs.put(page, freq);
}

#endif // AVLNODE_H
