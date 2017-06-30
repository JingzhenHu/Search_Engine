#include <iostream>
# include "avlnode.h"
#include "avltree.h"
#include "xmlparser.h"
#include "userinterface.h"
using namespace std;

int main(int argc, char *argv[])
{
    UserInterface user;
    user.chooseMode(/*argv[1]*/);
    cout << "Hello World!" << endl;
    return 0;
}
