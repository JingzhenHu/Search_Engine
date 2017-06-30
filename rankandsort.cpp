#include "rankandsort.h"

RankAndSort::RankAndSort(hashtable<long, int>& resultHashTable, EXAVLTree<long>& IDTree, long& totalNumOfPage)
{
    long size = resultHashTable.getDocNum();
    double doubleTemp = 0;
    long longTemp = 0;
    std::pair<double, long>* pairTemp = nullptr;
    for (long i = 0; i < resultHashTable.TABLE_SIZE; i++)
    {
        hashnode<long, int>* node = resultHashTable.table[i];
        while (node)
        {
            longTemp = node->getKey();
            doubleTemp = node->get_TFIDF(IDTree.getTotalNum(node->getKey()), totalNumOfPage, resultHashTable.getDocNum());
            pairTemp = new std::pair<double, long>(doubleTemp, longTemp);
            pairVec.push_back(*pairTemp);
            node = node->getNext();
        }
    }
}

void RankAndSort::Sort()
{
    std::sort(pairVec.begin(), pairVec.end(), [](const std::pair<double, long> &left, const std::pair<double, long> &right) {
        return left.first > right.first;
    });
}

void RankAndSort::printResult(EXAVLTree<long>& IDTree)
{
    if (pairVec.size() <= 15)
    {
        for (int i = 0; i < pairVec.size(); i++)
        {
            std::cout << i+1 << ". " << "\n";
            std::cout << "Page: " << pairVec[i].second << "\n";
            std::cout << "Title: " << IDTree.getTitle(pairVec[i].second) << "\n";
            std::cout << "Contributor Username: "<< IDTree.getContributor(pairVec[i].second)<<"\n";
            std::cout << "Time_Stamp: " << IDTree.getTime(pairVec[i].second) << "\n";
            std::cout << "TF-IDF: " << pairVec[i].first << "\n";
            //std::cout << "Text: " << IDTree.getText(pairVec[i].second) << "\n";
        }
    }
    else
    {
        for (int i = 0; i < 15; i++)
        {
            std::cout << i+1 << ". " << "\n";
            std::cout << "Page: " << pairVec[i].second << "\n";
            std::cout << "Title: " << IDTree.getTitle(pairVec[i].second) << "\n";
            std::cout << "Contributor Username: "<< IDTree.getContributor(pairVec[i].second)<<"\n";
            std::cout << "Time_Stamp: " << IDTree.getTime(pairVec[i].second) << "\n";
            std::cout << "TF-IDF: " << pairVec[i].first << "\n";
            //std::cout << "Text: " << IDTree.getText(pairVec[i].second) << "\n";
        }
    }
}

RankAndSort::~RankAndSort()
{

}
