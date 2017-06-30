/* @author Jingzhen Hu
 * Class Owner: Jingzhen Hu
 * This class is the EXAVLTree container for index. It has the basic fields of a EXAVLNode pointer.
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

#ifndef EXEXAVLTree_H
#define EXEXAVLTree_H
#include "exavlnode.h"
#include <iostream>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace rapidxml;

template <typename T>
class EXAVLTree
{
private:
    EXAVLNode<T>* root;
    /*rotation function for case 1*/
    void rotate_single_left(EXAVLNode<T>*& node) //case 1
    {
        EXAVLNode<T> *temp = node->getLeft();
        node->setLeft(temp->getRight());
        temp->setRight(node);
        temp->setHeight(max(height(temp->getLeft()),height(temp->getRight()))+1);
        node->setHeight(max(height(node->getLeft()),height(node->getRight()))+1);
        node = temp;
    }
    /*rotation function for case 4*/
    void rotate_single_right(EXAVLNode<T>*& node) //case 4
    {
        EXAVLNode<T> *temp = node->getRight();
        node->setRight(temp->getLeft());
        temp->setLeft(node);
        temp->setHeight(max(height(temp->getLeft()),height(temp->getRight()))+1);
        node->setHeight(max(height(node->getLeft()),height(node->getRight()))+1);
        node = temp;
    }
    /*rotation function for case 2*/
    void rotate_double_left(EXAVLNode<T>*& node)  //case 2
    {
        rotate_single_right(node->getLeft());
        rotate_single_left(node);
    }
    /*rotation function for case 3*/
    void roatet_double_right(EXAVLNode<T>*& node) //case 3
    {
        rotate_single_left(node->getRight());
        rotate_single_right(node);
    }
    /*insert important information of the ID tree in order to get information based on the pageID*/
    void _insert(const T& data, EXAVLNode<T>*& node, long& totalNum, string& text, string& title)
    {
        if(node == nullptr)
            node = new EXAVLNode<T>(data, totalNum, title, text);
        else if(data < node->getData())
        {
            _insert(data, node->getLeft(), totalNum, text, title);
            if( height(node->getLeft()) - height(node->getRight()) == 2)
                if(data < node->getLeft()->getData())
                    rotate_single_left(node);
                else
                    rotate_double_left(node);
        }
        else if(node->getData() < data)
        {
            _insert(data, node->getRight(), totalNum, text, title);
            if( height(node->getRight()) - height(node->getLeft()) == 2)
                if( node->getRight()->getData() < data)
                    rotate_single_right(node);
                else
                    roatet_double_right(node);
        }
        //will not be deuplicated
        node->setHeight(max(height(node->getLeft()), height(node->getRight())) + 1);
    }

    /*add with the contributor name in the overloaded _insert function */
    void _insert(const T& data, EXAVLNode<T>*& node, long& totalNum, string& text, string& title, string& timestamp, string& contributor)
    {
        if (node == nullptr)
            node = new EXAVLNode<T>(data, totalNum, title, text, timestamp, contributor);
        else if (data < node->getData())
        {
            _insert(data, node->getLeft(), totalNum, text, title, timestamp, contributor);
            if (height(node->getLeft()) - height(node->getRight()) == 2)
                if (data < node->getLeft()->getData())
                    rotate_single_left(node);
                else
                    rotate_double_left(node);
        }
        else if (node->getData() < data)
        {
            _insert(data, node->getRight(), totalNum, text, title, timestamp, contributor);
            if (height(node->getRight()) - height(node->getLeft()) == 2)
                if (node->getRight()->getData() < data)
                    rotate_single_right(node);
                else
                    roatet_double_right(node);
        }
        //will not be deuplicated
        node->setHeight(max(height(node->getLeft()), height(node->getRight())) + 1);
    }

    /*print the whole abl tree in order*/
    void printInOrder(EXAVLNode<T> *node) // a public method will call the method
    {
        if(node->getLeft() == nullptr && node->getRight() == nullptr)
        {
            std::cout << node->getData() << std::endl;
            std::cout << node->getTotalNum() << std::endl;
            std::cout << node->getTitle() << std::endl;
        }
        else
        {
            if(node->getLeft() != nullptr)
                printInOrder(node->getLeft());
            std::cout << node->getData() << std::endl;
            std::cout << node->getTotalNum() << std::endl;
            std::cout << node->getTitle() << std::endl;
            if(node->getRight() != nullptr)
                printInOrder(node->getRight());
        }
    }
    /*judge the certain word is exited in the tree or not*/
    bool find(EXAVLNode<T>*& node,T& data)
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
    /* claculate and return the amount of the words in the file*/
    long& getTotalNum(EXAVLNode<T>*& node,T& data)
    {
        if(data == node->getData())
        {
            return node->getTotalNum();
        }
        else
        {
            if(node->getData() < data)
            {
                if(node->getRight() != nullptr)
                    return getTotalNum(node->getRight(), data);
            }
            else if(node->getData() > data)
            {
                if(node->getLeft() != nullptr)
                    return getTotalNum(node->getLeft(), data);
            }
        }
    }
    /* calculate and return the amount of the pages in the xml file*/
    long& getTotalPage(EXAVLNode<T> *node, long& totalPage)
    {
        if (node->getLeft() == nullptr && node->getRight() == nullptr)
        {
            ++totalPage;
        }
        else
        {
            if (node->getLeft() != nullptr)
                getTotalPage(node->getLeft(), totalPage);
            ++totalPage;
            if (node->getRight() != nullptr)
                getTotalPage(node->getRight(), totalPage);
        }
        return totalPage;
    }
    /* get the text based on the pageid*/
    string& getText(EXAVLNode<T>*& node,T& data)
    {
        if(data == node->getData())
        {
            return node->getText();
        }
        else
        {
            if(node->getData() < data)
            {
                if(node->getRight() != nullptr)
                    return getText(node->getRight(), data);
            }
            else if(node->getData() > data)
            {
                if(node->getLeft() != nullptr)
                    return getText(node->getLeft(), data);
            }
        }
    }
    /* get the time based on the pageid*/
    string& getTime(EXAVLNode<T>*& node, T& data)
    {
        if (data == node->getData())
        {
            return node->getTimeStamp();
        }
        else
        {
            if (node->getData() < data)
            {
                if (node->getRight() != nullptr)
                    return getTime(node->getRight(), data);
            }
            else if (node->getData() > data)
            {
                if (node->getLeft() != nullptr)
                    return getTime(node->getLeft(), data);
            }
        }
    }
    /* get the contributor based on the pageid*/
    string& getContributor(EXAVLNode<T>*& node, T& data)
    {
        if (data == node->getData())
        {
            return node->getContributor();
        }
        else
        {
            if (node->getData() < data)
            {
                if (node->getRight() != nullptr)
                    return getContributor(node->getRight(), data);
            }
            else if (node->getData() > data)
            {
                if (node->getLeft() != nullptr)
                    return getContributor(node->getLeft(), data);
            }
        }
    }

    /* get the title based on the pageid*/
    string& getTitle(EXAVLNode<T>*& node,T& data)
    {
        if(data == node->getData())
        {
            return node->getTitle();
        }
        else
        {
            if(node->getData() < data)
            {
                if(node->getRight() != nullptr)
                    return getTitle(node->getRight(), data);
            }
            else if(node->getData() > data)
            {
                if(node->getLeft() != nullptr)
                    return getTitle(node->getLeft(), data);
            }
        }
    }
    /* write out in the disk as a xml file*/
    void writeInOrder(EXAVLNode<T> *node, xml_document<>*& doc, xml_node<> *& files) // a public method will call the method
    {
        if(node->getLeft() == nullptr && node->getRight() == nullptr)
        {
            xml_node<> *file = doc->allocate_node(node_element, "page");
            files->append_node(file);
            string buffer = to_string(node->getData());
            char* page = new char[buffer.length()+1];
            std::strcpy(page, buffer.c_str());
            xml_node<> *id = doc->allocate_node(node_element, "id", page);
            file->append_node(id);
            xml_node<> *title = doc->allocate_node(node_element, "title", node->getTitle().c_str());
            file->append_node(title);
            buffer = to_string(node->getTotalNum());
            char* char_number = new char[buffer.length()+1];
            strcpy(char_number, buffer.c_str());
            xml_node<> *word_number = doc->allocate_node(node_element, "word_number", char_number);
            file->append_node(word_number);
            xml_node<> *text = doc->allocate_node(node_element, "text", node->getText().c_str());
            file->append_node(text);
        }
        else
        {
            if(node->getLeft() != nullptr)
                writeInOrder(node->getLeft(), doc, files);
            xml_node<> *file = doc->allocate_node(node_element, "page");
            files->append_node(file);
            string buffer = to_string(node->getData());
            char* page = new char[buffer.length()+1];
            std::strcpy(page, buffer.c_str());
            xml_node<> *id = doc->allocate_node(node_element, "id", page);
            file->append_node(id);
            xml_node<> *title = doc->allocate_node(node_element, "title", node->getTitle().c_str());
            file->append_node(title);
            buffer = to_string(node->getTotalNum());
            char* char_number = new char[buffer.length()+1];
            strcpy(char_number, buffer.c_str());
            xml_node<> *word_number = doc->allocate_node(node_element, "word_number", char_number);
            file->append_node(word_number);
            xml_node<> *text = doc->allocate_node(node_element, "text", node->getText().c_str());
            file->append_node(text);
            if(node->getRight() != nullptr)
                writeInOrder(node->getRight(), doc, files);
        }
    }
public:
    /* constructor*/
    EXAVLTree():root(nullptr){}
    EXAVLTree(T& data, long& totalNum, string& title, string& text)
    {
        root = new EXAVLNode<T>(data, totalNum, title, text);
    }
    /* return root*/
    EXAVLNode<T>*& getRoot()
    {
        return root;
    }
    /* recurssive method call for the insert*/
    void insert(T& data, long& totalNum, string& title, string& text)
    {
        _insert(data, root, totalNum, text, title);
    }
    /* recurssive method call for the insert with more information*/
    void insert(T& data, long& totalNum, string& title, string& text, string& timestamp, string& contributor)
    {
        _insert(data, root, totalNum, text, title, timestamp, contributor);
    }
    /* clear all the tree*/
    void delete_all()
    {
        if(root != 0)
        {
            delete root;
            root = 0;
        }
        //std::cout << "Clear ALL The Data In IDTree" << std::endl;
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
    int height(EXAVLNode<T>* node)
    {
        if(node == nullptr)
            return -1;
        else
            return node->getHeight();
    }
    /* recurrsive method call for the printInOrder*/
    void printInOrder()
    {
        printInOrder(root);
    }
    /* recurrsive method call for the find*/
    bool find(T& data)
    {
        return find(root, data);
    }
    /*getters*/
    string& getText(T& data)
    {
        return getText(root, data);
    }

    string& getTitle(T& data)
    {
        return getTitle(root, data);
    }



    string& getTime(T& data)
    {
        return getTime(root, data);
    }

    string& getContributor(T& data)
    {
        return getContributor(root, data);
    }

    long& getTotalNode()
    {
        long totalPage = 0;
        return getTotalPage(root, totalPage);
    }


    long& getTotalNum(T& data)
    {
        return getTotalNum(root, data);
    }

    void writeXML()
    {
        xml_document<>* doc = new xml_document<>;
        xml_node<> *files = doc->allocate_node(node_element, "root");
        doc->append_node(files);
        writeInOrder(root, doc, files);
        std::ofstream myfile;
        myfile.open("IDTree.xml");
        myfile << *doc;
        myfile.close();
    }

    ~EXAVLTree()
    {
        delete_all();
    }
};

#endif // EXEXAVLTree_H
