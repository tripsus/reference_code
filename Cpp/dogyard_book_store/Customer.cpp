#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <string.h>
#include <vector>
#include "Customer.h"

using namespace std;

CustomerReader::CustomerReader(char *path):path(path) {
    
}
void CustomerReader::getInput(CustomerData* mCustomerData){
    char line[200];
    input.open(path.c_str());
    input.getline(line,200,'C');
    while(!input.eof()){
        input.getline(line,200,'C');
        mCustomerData->insert(line);
    }
}
CustomerData::CustomerData(BookDetails *b1){
        mBookDetails = b1;
        signature = 'C';
    }
void CustomerData::insert(char* line){
    char *token = strtok(line,",");
    bool firsttime = true;
    int customerId;
    int sum = 0;
    while(token != NULL){
        if(firsttime){
            customerId = atoi(token);
            
            int prev  = customerFrequency[customerId];
            customerFrequency[customerId] = prev+1;
            firsttime = false;
        }
        else{
            sum = sum + mBookDetails->fetchPrice(atoi(token+1));
            mBookDetails->insertQuantity(atoi(token+1));
        }
        token = strtok(NULL,",");
    }
    transactionDetails[customerId].push_back(sum);
}
void CustomerData::calculateFrequency(int size){
    Heap *maxCustomerHeap = new Heap(size, Heap::MAX_HEAP);
    map<int, int>::iterator it;
    for(it = customerFrequency.begin();it != customerFrequency.end();it++){
        maxCustomerHeap->insert(it->first,it->second);
    }
    maxCustomerHeap->printDetails(signature);
    maxCustomerHeap->cleanHeap();
}

void CustomerData::show(){
    map<int,int>::iterator it;
    for(it = customerFrequency.begin();it != customerFrequency.end();it++){
        cout<<it->first<<"   :";
        //for(int i=0;i<it->second.size();i++)
        cout<<it->second<<"   ";
        cout<<"\n";
    }
}
void CustomerData::getHighestTransaction(int size){
    Heap *highestTransactionHeap = new Heap(size, Heap::MAX_HEAP);
    map<int,vector<int> >::iterator it;
    for(it = transactionDetails.begin(); it!=transactionDetails.end();it++){
        for(int i=0;i<it->second.size();i++){
            highestTransactionHeap->insert(it->first,it->second[i]);
        }
    }
    highestTransactionHeap->printDetails(signature);
    highestTransactionHeap->cleanHeap();
}
bool CustomerData::checkEligiblity(int amount, int customerId){
    map<int,vector<int> >::iterator it;
    it = transactionDetails.find(customerId);
    int sum = 0;
    for(int i=0;i<it->second.size();i++)
        sum = sum + it->second[i];
    if(sum>amount)
        return 1;
    else
        return 0;
}