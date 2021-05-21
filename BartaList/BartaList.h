#ifndef _BARTA_LIST_
#define _BARTA_LIST_

#include"Node.h"
#include<iostream>
#include<functional>

#define _BARTA_SORTING_PREDICATE_FIRST(x) [](x n1, x n2){return true;}
#define _BARTA_SORTING_PREDICATE_LAST(x) [](x n1, x n2){return false;}

template<class T>
class BartaList
{
private:
    Node<T>* firstNode;
    std::function<bool(T&, T&)> sortingPredicate;

    bool callSortingPredicate(std::shared_ptr<T> data, Node<T>* checkedData);
    void forEachNode(std::function<bool(Node<T>*)> foo);
    void addWeakNodeAfter(Node<T>* node,std::shared_ptr<T> data);
    void addWeakFirstNode(std::shared_ptr<T> data);
    void addSharedNodeAfter(Node<T>* node, std::shared_ptr<T> data);
    void addSharedFirstNode(std::shared_ptr<T> data);
    void removeNextNode(Node<T>* node);
    void removeFirstNode();
public:
    BartaList(std::function<bool(T&,T&)> predicate);//TODO
    ~BartaList();
    void forEach(std::function<bool(T&)> foo);
    std::shared_ptr<T> findData(const T& data);
    void addWeakToList(std::shared_ptr<T> data);
    void addSharedToList(std::shared_ptr<T> data);
    void addSharedToList(T&& data);
    void remove(std::shared_ptr<T> data);
    void clear();
};

#include"BartaList.cpp"


#endif