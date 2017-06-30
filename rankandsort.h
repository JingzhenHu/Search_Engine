/*
 * Class Owner: Yichen Duan
 * This is a class for Tf-Idf rank and sort based on the results of ranking.
 * The field is just the pair of the ranked score and it corresponding pageid
 * After get the tf/idf score based on the totalPageNum, term appear times in that page,
 * and appearance in other pages.(calculation in hahsnode class), sort them based on
 * the score and print out the top 15.
 *
 * Changing history see the GitHub
 * */
#ifndef RANKANDSORT_H
#define RANKANDSORT_H
#include "hashtable.h"
#include <algorithm>
#include "exavltree.h"
#include <utility>
#include <vector>

class RankAndSort
{
private:
    std::vector<std::pair<double, long>> pairVec;
public:
    RankAndSort(hashtable<long, int>&, EXAVLTree<long>&, long&);
    void Sort();
    void printResult(EXAVLTree<long>&);
    ~RankAndSort();
};
#endif // RANKANDSORT_H
