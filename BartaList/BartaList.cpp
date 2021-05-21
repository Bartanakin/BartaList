#ifndef _BARTA_LIST_C
#define _BARTA_LIST_C

#include "BartaList.h"



template<class T>
bool BartaList<T>::callSortingPredicate(std::shared_ptr<T> data, Node<T>* checkedData)
{
    if (checkedData -> expired()) {
        return false;
    }
    else {
        return sortingPredicate(*(data), *(checkedData -> getData()));
    }
}

template<class T>
void BartaList<T>::forEachNode(std::function<bool(Node<T>*)> foo)
{
    Node<T>* buff = this->firstNode;
    while (buff != nullptr) {
        if (!foo(buff)) {
            break;
        }
        buff = buff->nextNode;
    }
}

template<class T>
void BartaList<T>::addWeakNodeAfter(Node<T>* node, std::shared_ptr<T> data)
{
    Node<T>* buff = new WeakNode<T>(data, node->nextNode);
    node->nextNode = buff;
}

template<class T>
void BartaList<T>::addWeakFirstNode(std::shared_ptr<T> data)
{
    Node<T>* buff = new WeakNode<T>(data, this->firstNode); ;
    this -> firstNode = buff;
}

template<class T>
void BartaList<T>::addSharedNodeAfter(Node<T>* node, std::shared_ptr<T> data)
{
    Node<T>* buff = new SharedNode<T>(data, node->nextNode);
    node->nextNode = buff;
}

template<class T>
void BartaList<T>::addSharedFirstNode(std::shared_ptr<T> data)
{
    Node<T>* buff = new SharedNode<T>(data, this->firstNode); ;
    this->firstNode = buff;
}

template<class T>
void BartaList<T>::removeNextNode(Node<T>* node)
{
    auto del = node->nextNode;
    node->nextNode = node->nextNode->nextNode;
    delete del;
}

template<class T>
void BartaList<T>::removeFirstNode()
{
    auto del = firstNode;
    firstNode = firstNode->nextNode;
    delete del;
}

template<class T>
BartaList<T>::BartaList(std::function<bool(T&,T&)> predicate)
:firstNode(nullptr),
sortingPredicate(predicate){
    
}

template<class T>
BartaList<T>::~BartaList()
{
    Node<T>* buff = this -> firstNode;
    while (buff != nullptr) {
        auto del = buff;
        buff = buff->nextNode;
        delete del;
    }
}

template<class T>
void BartaList<T>::forEach(std::function<bool(T&)> foo)
{
    Node<T>*  buff = this->firstNode;
    while (buff != nullptr) {
        if (!buff->expired() && !foo( *(buff->getData()) )) {
            break;
        }
        buff = buff->nextNode;
    }
}

template<class T>
void BartaList<T>::addWeakToList(std::shared_ptr<T> data)
{
    if (this->firstNode == nullptr || this->callSortingPredicate(data,firstNode)) {
        addWeakFirstNode(data);
    }
    else {
        this->forEachNode([&](Node<T>* node)->bool {
            if (node->nextNode == nullptr || this->callSortingPredicate(data, node-> nextNode)) {
                addWeakNodeAfter(node, data);
                return false;
            }
            return true;
        });
    }
    
}

template<class T>
void BartaList<T>::addSharedToList(std::shared_ptr<T> data)
{
    if (this->firstNode == nullptr || this->callSortingPredicate(data, firstNode)) {
        addSharedFirstNode(data);
    }
    else {
        this->forEachNode([&](Node<T>* node)->bool {
            if (node->nextNode == nullptr || this->callSortingPredicate(data, node->nextNode)) {
                addSharedNodeAfter(node, data);
                return false;
            }
            return true;
        });
    }
}

template<class T>
void BartaList<T>::addSharedToList(T&& data)
{
    std::shared_ptr<T> ptr = std::make_shared<T>(std::move(data));
    addSharedToList(ptr);
}

template<class T>
void BartaList<T>::remove(std::shared_ptr<T> data)
{
    if (data == nullptr) return;
    if ( firstNode != nullptr && !firstNode -> expired() && data == firstNode->getData()) {
        removeFirstNode();
    }
    else {
        forEachNode([&](Node<T>* node) {
            if (node->nextNode == nullptr) {
                return false;
            }
            if (node->nextNode->expired()) {
                this->removeNextNode(node);
                return true;
            }
            else if (*(node->nextNode -> getData()) == *(data)) {
                this->removeNextNode(node);
                return false;
            }
            return true;
        });
    }   
}

template<class T>
void BartaList<T>::clear()
{
    while (firstNode != nullptr && firstNode->expired()) {
        removeFirstNode();
        LOG("cleared!");
    }
    forEachNode([&](Node<T>* node) {
        if (node->nextNode == nullptr) {
            return false;
        }
        while( node->nextNode->expired() ) {
            LOG("cleared!");
            this->removeNextNode(node);
        }
        return true;
      });
    
}

template<class T>
std::shared_ptr<T> BartaList<T>::findData(const T& data)
{
    std::shared_ptr<T> ptr = nullptr;
    forEachNode([&](Node<T>* node) {
        if (!(node->expired())) {
            if (*(node->getData()) == data) {
                ptr = node->getData();
                return false;
            }
        }
        return true;
    });
    return ptr;
}

#endif