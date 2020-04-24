#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <QString>

/* Linked List */
class linkedList{

private:
    typedef struct node{
        QString data;
        node* next;
    }* nodePtr;     /* naming and function called defined as nodePtr */

    nodePtr head;
    nodePtr curr;
    nodePtr temp;

    /* This is where to functions goes to access private data */
public:
    linkedList();
    void addNode(QString addData);      /* Add a node and place a certain value in it */
    void deleteNode(int delData);   /* Whatever value is passed in here, will be searched through the list and removed */
    void printList();  /*  */
    void loadList(QString v);
    void print();
    int search(QString data);
    int loadSearch(QString data);
};

#endif // LINKEDLIST_H
