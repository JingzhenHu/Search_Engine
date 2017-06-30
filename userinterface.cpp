#include "userinterface.h"

/* @author JingzhenHu
 * deflaut constr
 * */
UserInterface::UserInterface():modeType(0),containerType(0),option(0){}

/*
 * function to interact with the user for the whole project
 * */
void UserInterface::chooseMode()
{
    std::cout << "Welcome to our Akinano_Hachiloku Search Engine!!!" << std::endl;
    std::cout << "Please choose the data structure to load the index:" <<std::endl;
    std::cout << "Option 1: AVL Tree" << std::endl;
    std::cout << "Option 2: Hash Table" << std::endl;
    //char* buffer = new char[];
    std::cin >> containerType;
    while(std::cin.fail() || (containerType != 1 && containerType != 2))
    {
        std::cin.clear();
        std::cout << "Invalid Input" << std::endl;
        std::cin.ignore(100,'\n');
        std::cin >> containerType;
    }
    ptr = new XMLParser(containerType);
    while(true)
    {
        std::cout << "Please Choose Mode: \n1 is the maintenance mode \n2 is the interactive mode\n3 quit!" << std::endl;
        std::cin >> modeType;
        while(std::cin.fail() || (modeType != 1 && modeType != 2 && modeType != 3))
        {
            std::cin.clear();
            std::cout << "Invalid Input" << std::endl;
            std::cin.ignore(100,'\n');
            std::cin >> modeType;
        }
        if(modeType == 3)
        {
            break;
        }
        if(modeType == 1)
        {
            std::cout << "Option 1: Creating the Index from the start point OR Adding documents to the Exiested Index\n       (@.@ CHOOSE ME WHEN USING THE FISRT TIME)" << std::endl;
            std::cout << "Option 2: Retrieve data structure from processed xml files\n      (&_&) WAITING FOR REPAIRS" << std::endl;
            std::cout << "Option 3: Clear all the index completetly\n      (X_X)" << std:: endl;
            std::cin >> option;
            while(std::cin.fail() || (option != 1 && option != 2 && option != 3))
            {
                std::cin.clear();
                std::cout << "Invalid Input" << std::endl;
                std::cin.ignore(100,'\n');
                std::cin >> option;
            }
            if(option == 1)
            {
                std::cout << "Please keep the xmlfile in the same folder of our execute file!" << std::endl;

                string filename;
                std::cout << "Please enter the filename that you want to load into the index!" << std::endl;
                std::cin >> filename;
                char* fname = new char[filename.length()+1];
                std::strcpy(fname, filename.c_str());
                /*using timer = std::chrono::high_resolution_clock;
                timer::time_point start_time = timer::now();*/
                ptr->readXML(fname);
                /*timer::time_point end_time = timer::now();
                std::cout << "Time elapsed: "
                          << std::chrono::duration_cast<std::chrono::milliseconds>(
                                 end_time - start_time).count() << "ms" << std::endl;*/
                modeType = 2;
            }
            else if(option == 2)
            {
                //waiting for the read function that will be finished in indexpersistence by Yichen
            }
            else if(option == 3)
            {
                //let the index call the delete_all
                ptr->getIndex()->delete_all();
                modeType = 2;
            }
        }
        if(modeType == 2)
        {
            std::cout << "Please enter a properly formatted boolean query:" << std::endl;
            string querySentence = "";
            string judge = "";
            std::cin >> judge;
            std::transform(judge.begin(), judge.end(), judge.begin(), ::tolower);
            if(!std::cin.eof())
            {
                getline(std::cin,querySentence);
            }
            int hasJudge = 0;
            if(judge == "and")
            {
                hasJudge = 1;
                if(option == 1)
                    QueryParser query(ptr->getIndex(), querySentence, hasJudge, ptr->getIDTree(), ptr->getPageNum());
            }
            else if(judge == "or")
            {
                hasJudge = 2;
                if(option == 1)
                    QueryParser query(ptr->getIndex(), querySentence, hasJudge, ptr->getIDTree(), ptr->getPageNum());
            }
            else
            {
                if(option == 1)
                    QueryParser query(ptr->getIndex(), querySentence, judge, ptr->getIDTree(), ptr->getPageNum());
            }
            if(option != 3)
            {
                //search and get the result ranked, sorted, print
                std::cout << "Do you want to display some relevant statistics about the index?(Y/N)" << std::endl;
                char y_n;
                std::cin >> y_n;
                while(std::cin.fail() || (containerType != 1 && containerType != 2))
                {
                    std::cin.clear();
                    std::cout << "Invalid Input" << std::endl;
                    std::cin.ignore(100,'\n');
                    std::cin >> y_n;
                }
                if(y_n == 'Y' || y_n == 'y')
                {
                    IndexPersistence obj;
                    obj.printStatisticData(ptr->getIDTree(),ptr->getIndex());
                }
            }
        }
    }
}
/*
 * destructor
 * */
UserInterface::~UserInterface()
{
    delete ptr;
}
