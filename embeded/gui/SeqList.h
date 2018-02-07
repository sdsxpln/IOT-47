//
// Created by song on 17-5-7.
//

#ifndef LINEARLIST5_SEQLIST_H
#define LINEARLIST5_SEQLIST_H

#include "LinearList.h"

template<class T>
class SeqList : public LinearList<T> {
private:
    int maxsize;
    T *array;

public:
    SeqList(int maxsize);

    bool IsEmpty() const override;

    int num() const override;

    bool Insert(int pos, T element) override;

    bool Delete(int pos) override;

    bool Update(int pos, const T &element) override;

    bool Find(int pos, T &element) const override;

    ~SeqList() override;
};

template<class T>
SeqList<T>::SeqList(int maxsize) : maxsize(maxsize) {
    this->n = 0;
    array = new T[maxsize];
}


template<class T>
bool SeqList<T>::IsEmpty() const {
    return (this->n == 0);
}

template<class T>
int SeqList<T>::num() const {
    return this->n;
}

template<class T>
bool SeqList<T>::Insert(int pos, T element) {
    if (pos < 0 || pos > this->n) {
        debug((uint8_t *) "Out Of Bounds.\n");
//        cout << "ERROR:Out Of Bounds" << endl;
        return false;
    }
    for (int i = pos + 1; i < this->n + 1; ++i) {
        array[i] = array[i - 1];
    }
    array[pos] = element;
    this->n++;
    return true;
}

template<class T>
bool SeqList<T>::Delete(int pos) {
    if (pos < 0 || pos > this->n - 1) {
        debug((uint8_t *) "Out Of Bounds.\n");
//        cout << "ERROR:Out Of Bounds" << endl;
        return false;
    }
    for (int i = pos; i < this->n - 1; ++i) {
        array[i] = array[i + 1];
    }

    this->n--;
    return true;
}

template<class T>
bool SeqList<T>::Update(int pos, const T &element) {
    if (pos < 0 || pos > this->n - 1) {
        debug((uint8_t *) "Out Of Bounds.\n");
//        cout << "ERROR:Out Of Bounds" << endl;
        return false;
    }
    array[pos] = element;
    return true;
}

template<class T>
bool SeqList<T>::Find(int pos, T &element) const {
    if (pos < 0 || pos > this->n - 1) {
        debug((uint8_t *) "Out Of Bounds.\n");
//        cout << "ERROR:Out Of Bounds" << endl;
        return false;
    }
    element = array[pos];

    return true;
}


template<class T>
SeqList<T>::~SeqList() {
    delete[] array;
    this->n = 0;
}


#endif //LINEARLIST5_SEQLIST_H
