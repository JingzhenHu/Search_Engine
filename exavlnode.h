/* @author Jingzhen Hu
 * Class Owner: Jingzhen Hu
 * This is the basic EXAVLnode template class that works for the EXAVLTree template class to store
 * the ID tree (original title, text, pageid, and total number of words for each document)
 * It contains fields of the template type T's data, long totalNum contains the total number
 * of words in each page(document), string text and title contain the original title and text.
 * The int height is to represent the height of the tree. The class also contains two itself pointers(right and left)
 * which is the basic characteristics for avl tree.
 * For methods, it is similar with the avl node.
 * It contains basic constructor, destructor, getters, and setters.
 *
 * Changing history see the GitHub
 * */

#ifndef EXEXAVLNode_H
#define EXEXAVLNode_H
#include <string>
#include <iostream>
using namespace std;
template <typename T>
class EXAVLNode
{
private:
    T data;
    long totalNum;
    string text;
    string title;
    string timestamp;
    string contributor;
    int height;
    EXAVLNode<T>* left;
    EXAVLNode<T>* right;
public:
    EXAVLNode();
    EXAVLNode(T ,long, string, string);
    EXAVLNode(T, long, string, string, string, string);
    ~EXAVLNode();
    long& getTotalNum();
    string& getTitle();
    string& getText();
    string& getTimeStamp();
    string& getContributor();
    T& getData();
    const T& getConst() const;
    int& getHeight();
    EXAVLNode<T>*& getLeft();
    EXAVLNode<T>*& getRight();
    void setData(T& t);
    void setLeft(EXAVLNode<T>*& l);
    void setRight(EXAVLNode<T>*& r);
    void setHeight(int h);
};
/*constructors*/
template <typename T>
EXAVLNode<T>::EXAVLNode():left(0),right(0),height(0){}
template <typename T>
EXAVLNode<T>::EXAVLNode(T t,long totalNum, string title, string text):data(t),totalNum(totalNum),title(title),text(text),right(0),left(0),height(0){}
template <typename T>
EXAVLNode<T>::EXAVLNode(T t, long totalNum, string title, string text, string timestamp, string contributor) : data(t), totalNum(totalNum), title(title), text(text), timestamp(timestamp),contributor(contributor), right(0), left(0), height(0){}
/*destrcutor*/
template <typename T>
EXAVLNode<T>::~EXAVLNode()
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
/*getters and setters*/
template <typename T>
long& EXAVLNode<T>::getTotalNum()
{
    return totalNum;
}

template <typename T>
string& EXAVLNode<T>::getTitle()
{
    return title;
}

template <typename T>
string& EXAVLNode<T>::getText()
{
    return text;
}


template <typename T>
string& EXAVLNode<T>::getTimeStamp()
{
    return timestamp;
}

template <typename T>
string& EXAVLNode<T>::getContributor()
{
    return contributor;
}

template <typename T>
T& EXAVLNode<T>::getData()
{
    return data;
}

template <typename T>
const T& EXAVLNode<T>::getConst() const
{
    return data;
}
template <typename T>
int& EXAVLNode<T>::getHeight()
{
    return height;
}
template <typename T>
EXAVLNode<T>*& EXAVLNode<T>::getLeft()
{
    return left;
}
template <typename T>
EXAVLNode<T>*& EXAVLNode<T>::getRight()
{
    return right;
}

template <typename T>
void EXAVLNode<T>::setData(T& t)
{
    data = t;
}
template <typename T>
void EXAVLNode<T>::setLeft(EXAVLNode<T>*& l)
{
    left = l;
}
template <typename T>
void EXAVLNode<T>::setRight(EXAVLNode<T>*& r)
{
    right = r;
}
template <typename T>
void EXAVLNode<T>::setHeight(int h)
{
    height = h;
}
#endif // EXEXAVLNode_H
