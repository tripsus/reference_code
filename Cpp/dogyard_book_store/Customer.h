/* 
 * File:   Customer.h
 * Author: MonsteR
 *
 * Created on May 17, 2015, 9:32 PM
 */

#ifndef CUSTOMER_H
#define	CUSTOMER_H
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cstdlib>
#include <string>
#include <string.h>

#include "Book.h"
#include "MyList.h"
using namespace std;
class CustomerData{
    map<int, int> customerFrequency;
    map<int,vector<int> > transactionDetails;
    BookDetails *mBookDetails;
public:
    char signature;
    CustomerData(BookDetails *b1);
    void insert(char *line);
    void show();
    void calculateFrequency(int size);
    void getHighestTransaction(int size);
    bool checkEligiblity(int amount, int customerId);
};
class CustomerReader{
    string path;
    fstream input;
public:
    CustomerReader(char *path);
    void getInput(CustomerData *mCustomerData);
};

#endif	/* CUSTOMER_H */

