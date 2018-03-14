#ifndef MYLIST_H
#define MYLIST_H
#include <cstdlib>

/**
*   an implementation of a dynamic list that can hold any type of data
**/

template <class T>
class MyList
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

template <class T>
MyList<T>::MyList(){
    head = NULL;
    last = NULL;
}

template <class T>
MyList<T>::~MyList(){
   // Node* p;
    //while(head){
    //    p = head;
    //    head = head->next;
    //    delete p;
    //}
}

template <class T>
void MyList<T>::push_front(T to_add){
    //creating a new Node
    Node* new_node = new Node;
    new_node->el = to_add;
    new_node->next = head;
    new_node->prev = NULL;

    head = new_node;

    if(!last){
        last = new_node;
    }
}

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

template <class T>
T MyList<T>::front(){
    return head->el;
}

template <class T>
T MyList<T>::back(){
    return last->el;
}

template <class T>
bool MyList<T>::empty(){
    if(head){
        return false;
    }
    return true;
}

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
