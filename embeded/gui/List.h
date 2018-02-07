//
// Created by song on 17-5-6.
//

#ifndef LINEARLIST5_LIST_H
#define LINEARLIST5_LIST_H

#include "LinearList.h"
#include "Node.h"

template<class T>
class List : public LinearList<T> {
private:
    Node<T> *head;
public:
    List();

    bool IsEmpty() const override;

    int num() const override;

    bool Insert(int pos, T element) override;

    bool Delete(int pos) override;

    bool Update(int pos, const T &element) override;

    bool Find(int pos, T &element) const override;

    T operator[](int pos);

    ~List() override;
};

template<class T>
bool List<T>::IsEmpty() const {
    return (this->n == 0);
}

template<class T>
int List<T>::num() const {
    return this->n;
}

template<class T>
bool List<T>::Insert(int pos, T element) {
    if (pos < 0 || pos > this->n) {
        return false;
    }
    Node<T> *tmp = head;
    for (int i = 0; i < pos; ++i) {
        tmp = tmp->next;
    }
    Node<T> *p = tmp->next;
    Node<T> *node = new Node<T>;
    node->data = element;
    tmp->next = node;
    node->next = p;
    this->n++;
    return true;
}

template<class T>
bool List<T>::Delete(int pos) {

    if (pos < 0 || pos > this->n - 1) {
        return false;
    }
    Node<T> *tmp = head;
    for (int i = 0; i < pos; ++i) {
        tmp = tmp->next;
    }
    Node<T> *q = tmp->next;
    Node<T> *p = q->next;
    tmp->next = p;
    delete q;
    this->n--;
    return true;

}

template<class T>
bool List<T>::Update(int pos, const T &element) {
    if (pos < 0 || pos > this->n - 1) {
        return false;
    }
    Node<T> *tmp = head;
    for (int i = 0; i < pos + 1; ++i) {
        tmp = tmp->next;
    }
    tmp->data = element;
    return true;
}

template<class T>
bool List<T>::Find(int pos, T &element) const {
    if (pos < 0 || pos > this->n - 1) {

        return false;
    }
    Node<T> *tmp = head;
    for (int i = 0; i < pos + 1; ++i) {
        tmp = tmp->next;
    }
    element = tmp->data;
    return true;
}

//template<class T>
//int List<T>::Search(T element) const {
//    Node<T> *tmp = head;
//    int i = 0;
//    for (i = 0; i < this->n; i++) {
//        tmp = tmp->next;
//        if (tmp->data == element) {
//            return i;
//        }
//    }
//    return -1;
//}

template<class T>
List<T>::~List() {
    for (int i = 0; i < this->n; i++) {
        Delete(this->n - i - 1);
    }

    delete head;
    this->n = 0;

}


template<class T>
T List<T>::operator[](int pos) {
    T element;
    Find(pos, element);
    return element;
}

template<class T>
List<T>::List() {
    this->n = 0;
    this->head = new Node<T>;
}

//template<class T>
//void List<T>::PrintInfo() const {
//    if (this->n <= 0) {
//
//    }
//    Node<T> *node = head;
//    for (int i = 0; i < this->n; ++i) {
//        node = node->next;
////        cout << node->data << " ";
////        print("%d ", node->data);
//    }
//    print("\n");
////    cout << endl;
//
//}


#endif //LINEARLIST5_LIST_H
