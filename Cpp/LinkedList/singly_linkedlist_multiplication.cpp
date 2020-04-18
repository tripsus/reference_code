#include <iostream>

using namespace std;

struct node {
    int val;
    node* next;
};
void printLL(node *productll){
    while(productll){
        cout<<productll->val<<"  ";
        productll = productll->next;
    }
    cout<<"\n";
}
void addNode(int value, node *curr){
    curr->next = new node();
    curr->next->val = value;
    curr->next->next = NULL;
}
node* createLL(int *arr, int size){
    node *head = NULL;
    node *curr = NULL;
    for(int i=0; i<size; i++){
        node *temp = new node();
        temp->val = arr[i];
        temp->next = NULL;
        if(head == NULL){
            head = temp;
            curr = temp;
        }else{
            curr->next = temp;
            curr = curr->next;
        }
    }
    return head;
}
node* multiplyLLUtil(node *upperll, int no, node *productll){
    if(upperll->next != NULL){
        productll = multiplyLLUtil(upperll->next, no, productll);
    }
    int product = (upperll->val * no) + productll->val;
    int carry = product/10;
    if(productll->next == NULL){
        addNode(0, productll);
    }
    productll->next->val = productll->next->val + carry;
    productll->val = product%10;
    //printLL(productll);
    return productll->next;
}

void multiplyLLUtilWrapper(node *upperll, int no, node *productll){
    multiplyLLUtil(upperll, no, productll);
}

node* multiplyLL(node *upperll, node *lowerll, node *productll){
    if(lowerll->next != NULL){
        productll = multiplyLL(upperll, lowerll->next, productll);
    }
    multiplyLLUtilWrapper(upperll, lowerll->val, productll);
    //printLL(productll);
    return productll->next;
}

node* reverseLL(node *head){
    node *current, *next, *previous;
    current = head;
    next = NULL;
    previous = NULL;
    while(current){
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    return previous;
}
int main(){
    int upper[] = {1,2,3};
    int lower[] = {4,5}; 
    node *upperll = createLL(upper, sizeof(upper)/sizeof(upper[0]));
    node *lowerll = createLL(lower, sizeof(lower)/sizeof(lower[0]));
    node *productll = new node();
    productll->val = 0;
    productll->next = NULL;
    multiplyLL(upperll, lowerll, productll);
    productll = reverseLL(productll);
    cout<<"Product of LL is ";
    printLL(productll);
    return 0;
}
