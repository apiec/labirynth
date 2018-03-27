#ifndef ORDEREDLIST_H
#define ORDEREDLIST_H

#include "Cell.h"
#include <cstdlib>

/** \brief A dynamic ordered list (a priority queue).
 *
 * This is a list that orders the elements as they are passed to it.
 * The smallest item is at the front.
 * The largest item is at the back
**/
template<class T>
class OrderedList
{
    private:

        /**
         * The node struct. Contains the element and pointers to the previous and next node.
        **/
        struct Node {
            T el;       /**< The element. */
            Node* next; /**< Pointer to the next node */
            Node* prev; /**< Pointer to the previous node */
        };

        Node* head;  /**< The first element of the list. The smallest one.*/
        Node* last;  /**< The last element of the list. The largest one. */

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

/**
 * Constructor. Sets the head and last to NULL.
**/
template<class T>
OrderedList<T>::OrderedList(){
    head = NULL;
    last = NULL;
}

/**
 * Destructor. Deletes all the nodes in the list.
**/
template<class T>
OrderedList<T>::~OrderedList(){
    Node* p;
    while(head){
        p = head;
        head = head->next;
        delete p;
    }
}

/** \brief Add an element to the list.
 * Creates a new Node and inserts it into the right place.
**/
template<class T>
void OrderedList<T>::append(T new_el){
    //create a new node
    Node* to_add = new Node;
    to_add->el = new_el;
    to_add->prev = NULL;
    to_add->next = NULL;

    Node* next = head;
    Node* prev = NULL;
    //search for the right place to place the new node
    //while there is a next node and the new element is bigger than the next element
    while(next && to_add->el > next->el){
        prev = next;
        next = next->next;
    }
    //if there is no prev it means the new node will be the new head
    if(prev){
        prev->next = to_add;
    }else{
        head = to_add;
    }
    //if there is no next it means the new node will be the new last
    if(next){
        next->prev = to_add;
    }else{
        last = to_add;
    }
    to_add->prev = prev;
    to_add->next = next;
}

/**
 * Delete the first element of the list.
**/
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

/**
 * Delete the last element of the list.
**/
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


/**
 * Return the first element of the list. Undefined behavior if the list is empty.
**/
template<class T>
T OrderedList<T>::front(){
    return head->el;
}

/**
 * Return the last element of the list. Undefined behavior if the list is empty.
**/
template<class T>
T OrderedList<T>::back(){
    return last->el;
}

/**
 * Returns true if the list is empty.
 * False if there are elements in the list.
**/
template<class T>
bool OrderedList<T>::empty(){
    return !head;
}

/**
 * Searches the list for the element that is equal (==) to the element that is passed as the argument.
**/
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

/**
 * Returns the number of the elements in the list.
**/
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
