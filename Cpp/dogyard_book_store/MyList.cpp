#include <iostream>
#include<stdio.h>
#include "MyList.h"
using namespace std;
Heap::Heap(int size,int type):type(type),size(size){
    list = new node*[size];
    for(int i=0;i<size;i++)
        list[i] = NULL;
    filled = 0;
}
node* MyList::addNode(int id,int value){
    node *temp = new node();
    temp->id = id;
    temp->value = value;
    temp->next = NULL;
    return temp;
}
void MyList::insert(node **head, node *currentNode){
    node *temp = *head;
    node *prev = NULL;
    while(1){
        if(lexicalSorter(currentNode->id,temp->id)){
            if(*head == temp){
                *head = currentNode;
            }
            currentNode->next = temp;
            prev->next = currentNode;
            break;
        }
        else{
            if(temp->next != NULL){
                prev = temp;
                temp = temp->next;
            }
            else{
                temp->next = currentNode;
                break;
            }
        }
    }
}
bool MyList::lexicalSorter(int a, int b){
	char ca[32];
	char cb[32];
	sprintf(ca,"%d",a);
	sprintf(cb,"%d",b);
	int lena = sizeof(ca);
	int lenb = sizeof(cb);
	int small = (lena<lenb)?lena:lenb;
	int i=0;
	for(;i<small;i++)
            if(ca[i] != cb[i])
                break;
	if(ca[i]<cb[i])
            return 1;
	else
            return 0;
}
void Heap::insert(int id, int value){
    int i = size -1;    
    /*TODO :: This search operation has complexity of 
      no of entries in map(n) * size of heap array(m)
     It can be reduced to n*log(m) if we use binary search tree AVL tree would be 
     * more efficient than Binary search Tree. */
    if(filled<size){
        while(list[i] != NULL && i>=0){
            if(value == list[i]->value){
                node *temp = MyList::addNode(id,value);
                MyList::insert(&list[i],temp);
                return;
            }
            i--;
        }
        if(i>=size/2){
            list[i] = MyList::addNode(id,value);
            filled++;
        }
        else{
            list[i] = MyList::addNode(id,value);
            filled++;
            if(type == Heap::MAX_HEAP)
                minHeapify(list,i,size-1);
            else{
                maxHeapify(list,i,size-1);
            }
        }
    }
    else{
        if((type == MAX_HEAP && value < list[0]->value) 
                ||(type == MIN_HEAP && value>list[0]->value))
            return;
        else {
            while(i>=0){
                if(value == list[i]->value){
                    node *temp = MyList::addNode(id,value);
                    MyList::insert(&list[i],temp);
                    return;
                }
            i--;
            }
        }
        if(type == MAX_HEAP && value>list[0]->value ){
            deleteList(list[0]);
            list[0] = list[size-1];
            list[size-1] = MyList::addNode(id,value);
            minHeapify(list,0,size-1);
        }
        else if(type == MIN_HEAP && value<list[0]->value){
            deleteList(list[0]);
            list[0] = list[size-1];
            list[size-1] = MyList::addNode(id,value);
            maxHeapify(list,0,size-1);
        }
    }
}
void Heap::maxHeapify(node** list, int i, int size){
    int leftChild = i*2+1;
    int rightChild = i*2 + 2;
    int smallerNode;
    if(leftChild <= size){
        if(rightChild > size)
            smallerNode = leftChild;
        else{
            smallerNode = ( (list[leftChild]->value)>(list[rightChild]->value) 
                                    ? leftChild : rightChild);
        }
        if(list[i]->value < list[smallerNode]->value){
            node *temp = list[i];
            list[i] = list[smallerNode];
            list[smallerNode] =  temp;
            i = smallerNode;
            if((2*i+1) <= size)
                maxHeapify(list,smallerNode,size);
        }
    }
}
void Heap::minHeapify(node** list, int i, int size){
    int leftChild = i*2+1;
    int rightChild = i*2 + 2;
    int smallerNode;
    if(leftChild <= size){
        if(rightChild > size)
            smallerNode = leftChild;
        else{
            smallerNode = ( (list[leftChild]->value)<(list[rightChild]->value) 
                                    ? leftChild : rightChild);
        }
        if(list[i]->value > list[smallerNode]->value){
            node *temp = list[i];
            list[i] = list[smallerNode];
            list[smallerNode] =  temp;
            i = smallerNode;
            if((2*i+1) <= size)
                maxHeapify(list,smallerNode,size);
        }
    }
}
void Heap::printDetails(char signature){
    int startIndex = size-filled;
    if(type == Heap::MAX_HEAP)
        maxHeapify(list,startIndex,size-1);
    else
        minHeapify(list,startIndex,size-1);
    int arraySize = size-1;
    for(int i=startIndex;i<=size-1;i++){
        node *head = list[startIndex];
        while(head){
            cout<<signature<<head->id<<" "<<head->value<<",";
            head = head->next;
        }
        node *temp = list[startIndex];
        list[startIndex] = list[arraySize];
        list[arraySize] = temp;
        if(type == Heap::MAX_HEAP)
            maxHeapify(list,startIndex,--arraySize);
        else
            minHeapify(list,startIndex,--arraySize);
    }
    cout<<"\n";
}
void Heap::deleteList(node* temp){
    if(temp->next != NULL)
        deleteList(temp->next);
    delete(temp);
}
void Heap::cleanHeap(){
    for(int i=(size-filled);i<size;i++)
        deleteList(list[i]);
    delete[] list;
}