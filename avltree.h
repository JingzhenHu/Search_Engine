/* @author Jingzhen Hu
 * Class Owner: Jingzhen Hu
 * This class is the AVLTree container for index. It has the basic fields of a AVLNode pointer,
 * a bool checkRepeat for cheak whether the words inserted is exited in the tree or not
 * It has many private methods including the four-case rotate situations, recursive methods
 * of _insert, printInOrder, writeXML, find and get
 * The insert function inserts the word in its right place with rotation if the word does not
 * exist in the tree, add the page in its ref without add the word repeatedly if the word does
 * exist, and add the frequency if both the word and the page is already existed in the tree.
 * The printInorder function traverses the whole tree and print the tree in order
 * The writeXML function works for the indexpersistence in order to write a xmlfile in disk
 * The find funtion will search(traverse) for whether the word is existed or not based on the words passing in
 * The get function is the function that is used after the find funtion, making sure the word can be found, and
 * then return the refs (lists of pages and frequencies) outside in order to deal with the two lists in a further way.
 * There are other methods for claculating heights, and comparing two int in order to choose a bigger one.
 * Besides, it also contains needed basic getters.
 *
 * Changing history see the GitHub
 * */

#ifndef AVLTREE_H
#define AVLTREE_H
#include "avlnode.h"
#include <iostream>
#include "indexinterface.h"
#include <string>
#include <cstring>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace rapidxml;
using namespace std;

template <typename T>
class AVLTree : public IndexInterface
{
private:
    AVLNode<T>* root;
    bool checkRepeat;
    /*rotation function for case 1*/
    void rotate_single_left(AVLNode<T>*& node) //case 1
    {
        AVLNode<T> *temp = node->getLeft();
        node->setLeft(temp->getRight());
        temp->setRight(node);
        temp->setHeight(max(height(temp->getLeft()),height(temp->getRight()))+1);
        node->setHeight(max(height(node->getLeft()),height(node->getRight()))+1);
        node = temp;
    }
    /*rotation function for case 4*/
    void rotate_single_right(AVLNode<T>*& node) //case 4
    {
        AVLNode<T> *temp = node->getRight();
        node->setRight(temp->getLeft());
        temp->setLeft(node);
        temp->setHeight(max(height(temp->getLeft()),height(temp->getRight()))+1);
        node->setHeight(max(height(node->getLeft()),height(node->getRight()))+1);
        node = temp;
    }
    /*rotation function for case 2*/
    void rotate_double_left(AVLNode<T>*& node)  //case 2
    {
        rotate_single_right(node->getLeft());
        rotate_single_left(node);
    }
    /*rotation function for case 3*/
    void roatet_double_right(AVLNode<T>*& node) //case 3
    {
        rotate_single_left(node->getRight());
        rotate_single_right(node);
    }
    /* if the word exists,and the page exists, add the frequency; if the words exits and the page is not, add the page
     * if the word doesn't exist, add the word with the page and set the frequency with 1*/
    void _insert(const T& data, AVLNode<T>*& node, long& page)
    {
        if(node == nullptr)
            node = new AVLNode<T>(data, page);
        else if(data < node->getData())
        {
            _insert(data, node->getLeft(), page);
            if( height(node->getLeft()) - height(node->getRight()) == 2)
                if(data < node->getLeft()->getData())
                    rotate_single_left(node);
                else
                    rotate_double_left(node);
        }
        else if(node->getData() < data)
        {
            _insert(data, node->getRight(), page);
            if( height(node->getRight()) - height(node->getLeft()) == 2)
                if( node->getRight()->getData() < data)
                    rotate_single_right(node);
                else
                    roatet_double_right(node);
        }
        else  //deuplicate, add the page and frequency at the end
        {
            checkRepeat = true;
            node->addRefs(page);
        }
        if(checkRepeat == false)
            node->setHeight(max(height(node->getLeft()), height(node->getRight())) + 1);
    }
    /*words for read in the xml file in the disk*/
    void _insert(const T& data, AVLNode<T>*& node, long& page, int& freq)
    {
        if(node == nullptr)
            node = new AVLNode<T>(data);
        else if(data < node->getData())
        {
            _insert(data, node->getLeft(), page);
            if( height(node->getLeft()) - height(node->getRight()) == 2)
                if(data < node->getLeft()->getData())
                    rotate_single_left(node);
                else
                    rotate_double_left(node);
        }
        else if(node->getData() < data)
        {
            _insert(data, node->getRight(), page);
            if( height(node->getRight()) - height(node->getLeft()) == 2)
                if( node->getRight()->getData() < data)
                    rotate_single_right(node);
                else
                    roatet_double_right(node);
        }
        else
        {
           node->setRefs(page, freq);
        }
        node->setHeight(max(height(node->getLeft()), height(node->getRight())) + 1);
    }
    /*print the whole abl tree in order*/
    void printInOrder(AVLNode<T> *node) // a public method will call the method
    {
        if(node->getLeft() == nullptr && node->getRight() == nullptr)
        {
            std::cout << node->getData() << std::endl;
            node->getRefs().printTable();
        }
        else
        {
            if(node->getLeft() != nullptr)
                printInOrder(node->getLeft());
            std::cout << node->getData() << std::endl;
            node->getRefs().printTable();
            if(node->getRight() != nullptr)
                printInOrder(node->getRight());
        }
    }
    /*judge the certain word is exited in the tree or not*/
    bool find(AVLNode<T>*& node,T& data)
    {
        if(node == nullptr)
        {
            return false;
        }
        if(data == node->getData())
        {
            return true;
        }
        else
        {
            if(node->getData() < data)
            {
                if(node->getRight() != nullptr)
                {
                    return find(node->getRight(), data);
                }
                else return false;
            }
            else if(node->getData() > data)
            {
                if(node->getLeft() != nullptr)
                {
                    return find(node->getLeft(), data);
                }
                else return false;
            }
        }
    }
    /* get the reference(pages and frequency) based on a certain word*/
    hashtable<long,int> get(AVLNode<T>*& node,T& data)
    {
        if(data == node->getData())
        {
            //node->getRefs().printTable();
            return node->getRefs();
        }
        else
        {
            if(node->getData() < data)
            {
                if(node->getRight() != nullptr)
                    return get(node->getRight(), data);
            }
            else if(node->getData() > data)
            {
                if(node->getLeft() != nullptr)
                    return get(node->getLeft(), data);
            }
        }
    }
    /* claculate the amount of the words in the index and return the value*/
    long getTotalWords(AVLNode<T> *node, long& totalWords) // a public method will call the method
    {
        if(node->getLeft() == nullptr && node->getRight() == nullptr)
        {
            ++totalWords;
        }
        else
        {
            if(node->getLeft() != nullptr)
                getTotalWords(node->getLeft(), totalWords);
            ++totalWords;
            if(node->getRight() != nullptr)
                getTotalWords(node->getRight(), totalWords);
        }
        return totalWords;
    }

public:
    /*constructor*/
    AVLTree():root(nullptr),checkRepeat(false){}
    /*getter*/
    AVLNode<T>*& getRoot()
    {
        return root;
    }
    /* recurssive method call for the insert*/
    void insert(T& data, long& page)
    {
        _insert(data, root, page);
    }
    /* clear all the tree*/
    void delete_all()
    {
        if(root != 0)
        {
            delete root;
            root = 0;
        }
        //std::cout << "Clear ALL The Data In WordTree" << std::endl;
    }
    /*comapre two num and return the bigger one*/
    int max(int x, int y)
    {
        if(x > y)
            return x;
        else
            return y;
    }
    /* return the height of tree*/
    int height(AVLNode<T>* node)
    {
        if(node == nullptr)
            return -1;
        else
            return node->getHeight();
    }
    /* recurrsive method call for the printInOrder*/
    void print()
    {
        printInOrder(root);
    }
    /* recurssive method calling fro the getTotalEords*/
    long getTotalNode()
    {
        long totalWords = 0;
        return getTotalWords(root, totalWords);
    }
    /* write the whole index tree in the disk as a xml file*/
    void writeInOrder(AVLNode<T> *node, xml_document<>*& doc, xml_node<> *& files) // a public method will call the method
    {
        if(node->getLeft() == nullptr && node->getRight() == nullptr)
        {
            xml_node<> *words = doc->allocate_node(node_element, "word");
            files->append_node(words);
            xml_node<> *name = doc->allocate_node(node_element, "name", node->getData().c_str());
            words->append_node(name);
            xml_node<> *value_pair = doc->allocate_node(node_element, "valuepair");
            words->append_node(value_pair);
            node->getRefs().writeXML(doc, value_pair);
        }
        else
        {
            if(node->getLeft() != nullptr)
                writeInOrder(node->getLeft(), doc, files);

            xml_node<> *words = doc->allocate_node(node_element, "word");
            files->append_node(words);
            xml_node<> *name = doc->allocate_node(node_element, "name", node->getData().c_str());
            words->append_node(name);
            xml_node<> *value_pair = doc->allocate_node(node_element, "valuepair");
            words->append_node(value_pair);
            node->getRefs().writeXML(doc, value_pair);


            if(node->getRight() != nullptr)
                writeInOrder(node->getRight(), doc, files);
        }
    }
    /* recurssive method to call the writeInOrder method*/
    void writeXML()
    {
        xml_document<>* doc = new xml_document<>;
        xml_node<> *files = doc->allocate_node(node_element, "root");
        doc->append_node(files);
        writeInOrder(root, doc, files);
        std::ofstream myfile;
        myfile.open("WordTree.xml");
        myfile << *doc;
        myfile.close();
    }
    /* recurrsive method call for the find*/
    bool find(T& data)
    {
        return find(root, data);
    }
    /* get the references*/
    hashtable<long,int> get(T& data)
    {
        return get(root, data);
    }

    ~AVLTree()
    {
        delete_all();
    }
};
#endif // AVLTREE_H
