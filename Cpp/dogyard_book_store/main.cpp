#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <string>
#include<string.h>
#include"Book.h"
#include "Customer.h"
#include "MyList.h"
using namespace std;
/*
	Class Book to store details of Book like Id, Price and Name
 * 
 * 1.Things to do: insert all those books into quantity sold which has not been sold 
 * 2. In insert function of Heap class check for the condition when 
 * 3. Implementation of Min heap
 * 
*/
void getFrequentCustomers(CustomerData *mCustomerData, int size){
    mCustomerData->calculateFrequency(size);
}
void getHighestTransaction(CustomerData *mCustomerData, int size){
    mCustomerData->getHighestTransaction(size);
}
void getHighestSellingBooks(BookDetails *mBookDetails, int size){
    mBookDetails->calculateQuantity(size);
}

void getLeastSellingBooks(BookDetails *mBookDetails, int size){
    mBookDetails->getLeastSellingBooks(size);
}
void isEligible(CustomerData *mCustomerData,int minAmount, char *id){
    int customerId = atoi(id+1);
    bool isEligible = mCustomerData->checkEligiblity(minAmount, customerId);
    if(isEligible)
        cout<<1;
    else
        cout<<0;
}

int main(int argc, char** argv){
	char *bookList =argv[4];//"test2.txt" ;//
    char *customerList =argv[2];//"test5.txt"; //
    cout<<booklist;
    cout<<customerList;
    BookDetails *mBookDetails = new BookDetails();
	BookDetailReader mBookDetailReader(bookList);
	mBookDetailReader.getInput(mBookDetails);
    CustomerData *mCustomerData = new CustomerData(mBookDetails);
    CustomerReader *mCustomerReader = new CustomerReader(customerList);
    mCustomerReader->getInput(mCustomerData);
    if(argc == 7){
        int no=atoi(argv[6]);
        getFrequentCustomers(mCustomerData,no);
        getHighestTransaction(mCustomerData, no);
        getHighestSellingBooks(mBookDetails,no);
        getLeastSellingBooks(mBookDetails, no);
        }
    else{
        int minAmount = atoi(argv[6]);
        char *customerId = argv[8];
        isEligible(mCustomerData,minAmount,customerId);
    }
	return 0;
}
