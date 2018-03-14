#ifndef ORDEREDLIST_H
#define ORDEREDLIST_H

#include "Cell.h"
#include <cstdlib>

/**
* this is an implemented priority queue
* the smallest item is at the front
* the biggest item is at the back
**/
template<class T>
class OrderedList
{
    private:

        struct Node {
            T el; //element
            Node* next;
            Node* prev;
        };

        Node* head;
        Node* last;

    public:

        void append(T to_add);
        void pop_front();
        void pop_back();
        T front();
        T back();
        bool empty();
        bool contains(T to_check);
        std::size_t size();

        OrderedList();
        ~OrderedList();
};

template<class T>
OrderedList<T>::OrderedList(){
    head = NULL;
    last = NULL;
}

template<class T>
OrderedList<T>::~OrderedList(){
    Node* p;
    while(head){
        p = head;
        head = head->next;
        delete p;
    }
}
template<class T>
void OrderedList<T>::append(T new_el){
    Node* to_add = new Node;
    to_add->el = new_el;
    to_add->prev = NULL;
    to_add->next = NULL;

    Node* next = head;
    Node* prev = NULL;

    while(next && to_add->el > next->el){
        prev = next;
        next = next->next;
    }

    if(prev){
        prev->next = to_add;
    }else{
        head = to_add;
    }
    if(next){
        next->prev = to_add;
    }else{
        last = to_add;
    }
    to_add->prev = prev;
    to_add->next = next;
}

template<class T>
void OrderedList<T>::pop_front(){

    if(!head) return;

    Node* p = head;
    head = head->next;
    if(head){
        head->prev = NULL;
    }else{
        last = NULL;
    }
    delete p;
}

template<class T>
void OrderedList<T>::pop_back(){

    if(!last) return;

    Node* p = last;
    last = last->prev;
    if(last){
        last->next = NULL;
    }else{
        head = NULL;
    }
    delete p;
}

template<class T>
T OrderedList<T>::front(){
    return head->el;
}

template<class T>
T OrderedList<T>::back(){
    return last->el;
}

template<class T>
bool OrderedList<T>::empty(){
    return !head;
}

template<class T>
bool OrderedList<T>::contains(T to_check){
    Node* p = head;
    while(p){
        if(p->el == to_check){
            return true;
        }
        p = p->next;
    }
    return false;
}

template<class T>
std::size_t OrderedList<T>::size(){
    std::size_t sz = 0;
    Node* p = head;
    while(p){
        p = p->next;
        sz++;
    }
    return sz;
}

#endif // ORDEREDLIST_H
