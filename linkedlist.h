#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/* Linked List */
class linkedList{

private:
    typedef struct node{
        int data;
        node* next;
    }* nodePtr;     /* naming and function called defined as nodePtr */

    nodePtr head;
    nodePtr curr;
    nodePtr temp;

public: /* This is where to functions goes to access private data */
    linkedList();
    void addNode(int addData);      /* Add a node and place a certain value in it */
    void deleteNode(int delData);   /* Whatever value is passed in here, will be searched through the list and removed */
    void printList();               /*  */
};

#endif // LINKEDLIST_H
