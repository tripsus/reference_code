/* 
 * File:   MyList.h
 * Author: MonsteR
 *
 * Created on May 17, 2015, 12:26 AM
 */

#ifndef MYLIST_H
#define	MYLIST_H
#include <iostream>
using namespace std;
struct node{
    int id;
    int value;
    node *next;
};
class MyList{
public:
    
    MyList(int size, int type);
    static node* addNode(int id, int value);
    static void insert(node **node, struct node *currentNode);
    static bool lexicalSorter(int a, int b);
};
class Heap{
    node **list;
    const int size;
    const int type;
    int filled;
public:
    static const int MAX_HEAP = 1;
    static const int MIN_HEAP = 2;
    Heap(int size, int type);
    void minHeapify(node **list,int i,int size);
    void maxHeapify(node **list,int i,int size);
    void insert(int id, int value);
    void printDetails(char signature);
    void deleteList(node *temp);
    void cleanHeap();
};
/*Heap::MAX_HEAP = 1;
Heap::MIN_HEAP = 2;*/



#endif	/* MYLIST_H */

