#include <iostream>

using namespace std;
struct node {
    int value;
    node *next;
    node *previous;
};

void traverseLL(node *pHead){
    while(pHead != NULL){
        cout<<pHead->value<<" ";
        pHead = pHead->next;
    }
}
void addNodeLeft(int value, node **head){
    node *temp = new node();
    temp->value = value;
    temp->next = NULL;
    temp->previous = NULL;
    if(*head != NULL){
        (*head)->previous = temp;
        temp->next = *head;
    }
    *head = temp;
}

node* addNodeRight(int value, node **head){
    node *temp = new node();
    temp->value = value;
    temp->next = NULL;
    temp->previous = NULL;
    if(*head == NULL){
        *head = temp;    
    }else{
        node *trav = *head;
        while(trav->next != NULL){
            trav = trav->next;
        }
        trav->next = temp;
        temp->previous = trav;
    }
    return temp;
}
void addLeft(int no, node *productTraverse, node **productLL){
    if(productTraverse->previous == NULL){
        addNodeLeft(no, productLL);
    }else{
        productTraverse = productTraverse->previous;
        int sum = productTraverse->value + no;
        if(sum/10){
            addLeft(sum/10, productTraverse, productLL);
        }
        productTraverse->value = sum%10;
    }
}
void add(int no, node** productTraverse, node **productLL){
    if((*productTraverse) == NULL){
        *productTraverse = addNodeRight(no, productLL);
    }else{
        int sum = (*productTraverse)->value + no;
        if(sum/10){
            addLeft(sum/10, *productTraverse, productLL);
        }
        (*productTraverse)->value = sum%10;
    }
}

node* multiplyLL(node *a, node *b){
    node *aTemp = a;
    node *bTemp = b;
    node *productLL = NULL;
    node *productTraverse = NULL;
    node *prevPostion = NULL;
    while(aTemp != NULL){   
        int multiplier = aTemp->value;
        bTemp = b;
        while(bTemp != NULL){
            if(productLL == NULL){
                addNodeRight(0, &productLL);
                prevPostion = productLL;
                productTraverse = prevPostion;
            }else{
                if(productTraverse->next == NULL){
                    productTraverse = addNodeRight(0, &productLL);
                }else{
                    productTraverse = productTraverse->next;
                }
            }
            int no = bTemp->value;
            int product = multiplier * no + productTraverse->value;
            productTraverse->value = 0;
            if(product/10){
                addLeft(product/10, productTraverse, &productLL);
            }
            add(product%10, &productTraverse, &productLL);
            bTemp = bTemp->next;
        }
        aTemp = aTemp->next;
        productTraverse = prevPostion;
        if(prevPostion->next == NULL && aTemp != NULL){
            addNodeRight(0, &productLL);
        }
        prevPostion = prevPostion->next;
    }
    return productLL;
}
int main(){
    int a[] = {9,2, 1,3,4};
    int b[] = {9,2};
    struct node *pHead, *aHead, *bHead;
    pHead = aHead = bHead = NULL;
    int aSize = sizeof(a)/sizeof(a[0]);
    int bSize = sizeof(b)/sizeof(b[0]);
    for(int i=0; i<aSize; i++){
        addNodeRight(a[i], &aHead);
    }
    //traverseLL(aHead);
    for(int i=0; i<bSize; i++){
        addNodeRight(b[i], &bHead);
    }
    //traverseLL(bHead);
    pHead = multiplyLL(aHead, bHead);
    traverseLL(pHead);
    return 0;
}   