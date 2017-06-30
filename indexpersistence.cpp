#include "IndexPersistence.h"

IndexPersistence::IndexPersistence()
{

}

void IndexPersistence::write_IDTree_XML(EXAVLTree<long>& IDTreeForXML)
{
    IDTreeForXML.writeXML();
}

void IndexPersistence::write_WordTree_XML(IndexInterface*& WordTreeForXML)
{
    WordTreeForXML->writeXML();
}

void IndexPersistence::write_XML(EXAVLTree<long>& IDTreeForXML, IndexInterface*& WordTreeForXML)
{
    write_IDTree_XML(IDTreeForXML);
    write_WordTree_XML(WordTreeForXML);
}

void IndexPersistence::printStatisticData(EXAVLTree<long>& IDTreeForXML, IndexInterface*& WordTreeForXML)
{
    std::cout << "Total number of pages: " << IDTreeForXML.getTotalNode() << " pages\n";
    std::cout << "Total number of words: " << WordTreeForXML->getTotalNode() << " words\n\n";

}

EXAVLTree<long>& IndexPersistence::getIDTree()
{
    return IDTree;
}

IndexInterface*& IndexPersistence::getWordTree()
{
    return WordTree;
}

IndexPersistence::~IndexPersistence()
{

}
