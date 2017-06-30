/* @author Jingzhen Hu
 * Class Owner: Jingzhen Hu
 * This is the UserInterface class that combination all the funtion together.
 * It is a basic interaction with th user. First, let them to choose which data structure
 * to store data, and it provides the maintenance mode (adding & clear files) and
 * iteractive mode (queryer and search words). It also can show some statistic related to the files
 *
 * Changing history see the GitHub
 * */

#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <string>
#include <cstring>
#include <iostream>
#include <chrono>
#include "xmlparser.h"
#include "queryparser.h"
//#include "indexpersistence.h"
using std::string;

class UserInterface
{
private:
    int modeType;           // 0 is maintenance mode and 1 is the interactive mode
    int containerType;      // 0 is the HashTable and 1 is the AVL Tree
    int option;
    XMLParser* ptr;

public:

    UserInterface();
    void chooseMode();
    ~UserInterface();
};

#endif // USERINTERFACE_H
