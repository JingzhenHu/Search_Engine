#include "queryparser.h"
/* overloaded constructor for and/or
 * @parameter index is a pointer of indexinterface which can be implemented as either avl tree or hashtable
 * string sten is the queryer sentence that passing in to be dealed with
 * int judge is to judge the first word is AND or OR
 * the IDTree and totalPage is to build the RankAndSort OBJC
 * */
QueryParser::QueryParser(IndexInterface*& index, string sten, int judge, EXAVLTree<long>& IDTree, long& totalPage)
{
    hasNOT = false;
    vector<string> splits;
    middleProcess(sten, splits);
    prepareField(splits);
    if(index->find(words[0]))
        results = index->get(words[0]);
    if(judge == 1)
    {
        hasAND = true;
        hasOR = false;
        for(int i = 1; i < words.size(); i++)
        {
            if(index->find(words[i]))
            {
                hashtable<long,int> refs = index->get(words[i]);
                results.combinAND(refs);
            }
        }
    }
    else
    {
        hasOR = true;
        hasAND = false;
        for(int i = 1; i < words.size(); i++)
        {
            if(index->find(words[i]))
            {
                hashtable<long,int> refs = index->get(words[i]);
                results.combinOR(refs);
            }
        }
    }
    if(hasNOT == true)
    {
        for(int i = 0; i < except.size();i++)
        {
            if(index->find(except[i]))
            {
                hashtable<long, int> refs = index->get(except[i]);
                results.combinNOT(refs);
            }
        }
    }
    /*
    if(!results.isEmpty())
        results.printTable();
    else
        std::cout << "No result for such words!!" << std::endl;*/
    RankAndSort ras(results, IDTree, totalPage);
    ras.Sort();
    ras.printResult(IDTree);
}

/* overloaded constructor for single word (canbe with NOT or not)
 * @parameter index is a pointer of indexinterface which can be implemented as either avl tree or hashtable
 * string sten is the queryer sentence that passing in to be dealed with
 * string firstWord is the single word to search (before the NOT or not)
 * the IDTree and totalPage is to build the RankAndSort OBJC
 * */
QueryParser::QueryParser(IndexInterface*& index, string& sten, string& firstWord, EXAVLTree<long>& IDTree, long& totalPage)
{
    hasAND = false;
    hasOR = false;
    hasNOT = false;
    vector<string> splits;
    std::transform(firstWord.begin(), firstWord.end(), firstWord.begin(), ::tolower);
    splits.push_back(firstWord);
    middleProcess(sten, splits);
    prepareField(splits);
    if(index->find(splits[0]))
    {
        results = index->get(splits[0]);
        if(hasNOT == true)
        {
            for(int i = 0; i < except.size();i++)
            {
                if(index->find(except[i]))
                {
                    hashtable<long, int> refs = index->get(except[i]);
                    results.combinNOT(refs);
                }
            }
        }
    }
    /*
    if(!results.isEmpty())
        results.printTable();
    else
        std::cout << "No result for such words!!" << std::endl;*/
    RankAndSort ras(results, IDTree, totalPage);
    ras.Sort();
    ras.printResult(IDTree);
}

/*
 * @parameter sten is the queryer sentence; splits is the vector to accept the processed words for searching
 * The method is to eliminate the stop words, clear special chars, transform to lowercase, stemming, and spliting
 * */
void QueryParser::middleProcess(string& sten, vector<string>& splits)
{
    ifstream file;
    file.open("StopWordII.txt");
    if(file.is_open())
    {
        while(!file.eof())
        {
            std::string eachWord;
            std::getline(file,eachWord);
            stopwords.insert(eachWord);
        }
        file.close();
    }
    clearSpecialChars(sten);
    std::transform(sten.begin(), sten.end(), sten.begin(), ::tolower);
    std::istringstream stp (sten);
    eliminateStop(splits, stp);
    stemming(splits);
}
/*@parameter splits is the words to search
 * the method is to speperate the splits vector into the words vector and except vector two parts
 * */
void QueryParser::prepareField(vector<string>& splits)
{
    for(int i = 0; i < splits.size(); i++)
    {
        if(splits[i] == "not")
        {
            hasNOT = true;
            for(int j = i+1; j < splits.size(); j++)
                except.push_back(splits[j]);
            for(int k = 0; k < i; k++)
                words.push_back(splits[k]);
            break;
        }
    }
    if(hasNOT == false)
    {
        for(int i = 0; i < splits.size(); i++)
            words.push_back(splits[i]);
    }
}
/*
 * @paramter word is a preprocessed queryer string
 * the method is to clear special chars
 * */
void QueryParser::clearSpecialChars(std::string &word)
{
    int i = 0;
    for (string::iterator it = word.begin(); it < word.end(); it++, i++)
    {
        if (!isalpha(word[i]))
        {
            word[i] = ' ';
        }
    }
}

/*
 * @paramter vector is to accept the splits words, word is the istringstream will be splited
 * the method is to eliminate stop words and put the processed word into a vector
 * */
void QueryParser::eliminateStop(vector<string>& vector, istringstream& word)
{
    std::string buffer = "";
    while(!word.eof())
    {
        word>>buffer;
        if(stopwords.find(buffer) == stopwords.end())
        {
            vector.push_back(buffer);
        }
    }
}
/*
 * @paramter splits is the vector of words to search
 * the method is to stem each word
 * */
void QueryParser::stemming(vector<string>& splits)
{
    for(int i = 0; i < splits.size(); i++)
    {
        Porter2Stemmer::stem(splits[i]);
    }
}
