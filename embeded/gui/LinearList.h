//
// Created by song on 17-5-6.
//

#ifndef LINEARLIST5_LINEARLIST_H
#define LINEARLIST5_LINEARLIST_H

#include "usart.h"

template<class T>
class LinearList {
protected:
    int n;
public:
    virtual bool IsEmpty() const = 0;

    virtual int num() const = 0;

    virtual bool Insert(int pos, T element) = 0;

    virtual bool Delete(int pos) = 0;

    virtual bool Update(int pos, const T &element) = 0;

    virtual bool Find(int pos, T &element) const = 0;


    virtual ~LinearList();
};

template<class T>
LinearList<T>::~LinearList() {

}


#endif //LINEARLIST5_LINEARLIST_H
