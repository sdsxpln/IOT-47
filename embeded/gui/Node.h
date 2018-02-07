//
// Created by song on 17-5-6.
//

#ifndef LINEARLIST5_NODE_H
#define LINEARLIST5_NODE_H

template <class T>
class List;

template <class T>
class Node{
    friend class List<T>;
private:
    T data;
    Node* next;
};

#endif //LINEARLIST5_NODE_H
