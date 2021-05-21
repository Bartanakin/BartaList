#ifndef _BARTA_NODE_
#define _BARTA_NODE_

#include<memory>
#include"DebugSettings.h"

template<class T>
class Node
{
public:
    Node<T>* nextNode;

    Node(Node<T>* next = nullptr);
    virtual bool expired() = 0;
    virtual void setData(std::shared_ptr<T> data) = 0;
    virtual std::shared_ptr<T> getData() = 0;

};

template<class T>
class WeakNode :public Node<T> {
    std::weak_ptr<T> data;
public:

    WeakNode(std::shared_ptr<T> data, Node<T>* next = nullptr);
    bool expired();
    inline void setData(std::shared_ptr<T> data) { this->data = data; };
    std::shared_ptr<T> getData(); 

};

template<class T>
class SharedNode :public Node<T> {
    std::shared_ptr<T> data;
public:

    SharedNode(std::shared_ptr<T> data, Node<T>* next = nullptr);
    bool expired();
    inline void setData(std::shared_ptr<T> data) { this->data = data; };
    inline std::shared_ptr<T> getData() { return this->data; };

};
#include "Node.cpp"

#endif


