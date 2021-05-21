#ifndef _BARTA_NODE_C
#define _BARTA_NODE_C
#include "Node.h"

template<class T>
Node<T>::Node(Node<T>* next)
    :nextNode(next)
    {}

template<class T>
WeakNode<T>::WeakNode( std::shared_ptr<T> data,Node<T>* next)
    :Node<T>(next),
    data(data)
    {}

template<class T>
bool WeakNode<T>::expired()
{
    return this -> data.expired();
}

template<class T>
std::shared_ptr<T> WeakNode<T>::getData()
{
    if (expired()) return nullptr;
    return std::shared_ptr<T>(this->data);
};

template<class T>
SharedNode<T>::SharedNode(std::shared_ptr<T> data, Node<T>* next)
    :Node<T>(next),
    data(data)
    {}

template<class T>
bool SharedNode<T>::expired()
{
    return false;
}
#endif