#ifndef MYLIST_H
#define MYLIST_H
#include <cstdlib>

/** \brief A dynamic list.
 *
 * A dynamic list that has many of the functionalities of the standard C++ list.
 * It can hold any data type.
**/

template <class T>
class MyList
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

        Node* head;  /**< The first element of the list. */
        Node* last;  /**< The last element of the list.  */

    public:

        void push_front(T to_add);
        void push_back(T to_add);
        void pop_front();
        void pop_back();
        T front();
        T back();
        bool empty();
        std::size_t size();

        MyList();
        ~MyList();
};

/**
 * Constructor. Sets the head and last to NULL.
**/
template <class T>
MyList<T>::MyList(){
    head = NULL;
    last = NULL;
}

/**
 * Destructor. Deletes all the nodes in the list.
**/
template <class T>
MyList<T>::~MyList(){
    Node* p;
    while(head){
        p = head;
        head = head->next;
        delete p;
    }
}
/**
 * Add an element to the front of the list.
**/
template <class T>
void MyList<T>::push_front(T to_add){
    //creating a new Node
    Node* new_node = new Node;
    new_node->el = to_add;
    new_node->next = head;
    new_node->prev = NULL;

    if(head){
        head->prev = new_node;
    }
    head = new_node;
    //if there is no last the list is empty, so it needs to be set
    if(!last){
        last = new_node;
    }
}

/**
 * Add an element to the back of the list.
**/
template <class T>
void MyList<T>::push_back(T to_add){
    //creating a new Node
    Node* new_node = new Node;
    new_node->el = to_add;
    new_node->next = NULL;
    new_node->prev = last;

    if(last){
        last->next = new_node;
    }

    last = new_node;

    if(!head){
        head = new_node;
    }
}

/**
 * Delete the first element of the list.
**/
template <class T>
void MyList<T>::pop_front(){

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
template <class T>
void MyList<T>::pop_back(){

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
template <class T>
T MyList<T>::front(){
    return head->el;
}

/**
 * Return the last element of the list. Undefined behavior if the list is empty.
**/
template <class T>
T MyList<T>::back(){
    return last->el;
}

/**
 * Returns true if the list is empty.
 * False if there are elements in the list.
**/
template <class T>
bool MyList<T>::empty(){
    if(head){
        return false;
    }
    return true;
}

/**
 * Returns the number of the elements in the list.
**/
template <class T>
std::size_t MyList<T>::size(){
    std::size_t sz = 0;
    Node* p = head;
    while(p){
        p = p->next;
        sz++;
    }
    return sz;
}


#endif // MYLIST_H
