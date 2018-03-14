#ifndef ORDEREDLIST_H
#define ORDEREDLIST_H

#include "MyList.h"

template <class T>
class OrderedList : protected MyList
{
    private:
        struct Node {
            T el;
            int value;
            prev* Node;
            next* Node;
        };

    protected:

    public:
        OrderedList();
        ~OrderedList();

};

#endif // ORDEREDLIST_H
