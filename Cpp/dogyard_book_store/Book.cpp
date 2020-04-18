#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <string>
#include <string.h>
#include <cmath>
#include"Book.h"
#include "MyList.h"
using namespace std;


Book::Book(){
    count = 1;
}
void Book::tokenizer(char *line){
        char *token = strtok(line,",");
        while(token != NULL){
                if(count == 1){
                        bookId = atoi(token+1);
                        count++;
                }
                else if(count == 2){
                        bookPrice = atoi(token);
                        count++;
                }
                else{
                        count = 1;
                }
                token = strtok(NULL,",");
        }
}



BookDetails::BookDetails(){
        count = 0;
        signature = 'P';
}
void BookDetails::insertPrice(const Book *b){
        bookPrice[b->bookId] = b->bookPrice;
        quantitySold[b->bookId] = 0;
}
int BookDetails::fetchPrice(int bookId){
    return bookPrice[bookId];
}
void BookDetails::insertQuantity(int bookId){
    int prev = quantitySold[bookId];
    quantitySold[bookId] = ++prev;
}
int BookDetails::fetchQuantity(int bookId){
    return quantitySold[bookId];
}
void BookDetails::calculateQuantity(int size){
    Heap *highestSellingHeap = new Heap(size, Heap::MAX_HEAP);
    map<int, int>::iterator it;
    for(it = quantitySold.begin();it != quantitySold.end();it++){
        highestSellingHeap->insert(it->first,it->second);
    }
    highestSellingHeap->printDetails(signature);
    highestSellingHeap->cleanHeap();
}
void BookDetails::getLeastSellingBooks(int size){
    Heap *leastSellingBookHeap = new Heap(size, Heap::MIN_HEAP);
    map<int, int>::iterator it;
    for(it=quantitySold.begin();it != quantitySold.end();it++)
        leastSellingBookHeap->insert(it->first,it->second);
    leastSellingBookHeap->printDetails(signature);
    leastSellingBookHeap->cleanHeap();
}

BookDetailReader::BookDetailReader(char *path):path(path){
}
void BookDetailReader::getInput(BookDetails *mBookDetails){
        char line[200];
        input.open(path.c_str());
        Book *mBook = new Book();
        while(!input.eof()){
                input.getline(line,200);
                mBook->tokenizer(line);
                mBookDetails->insertPrice(mBook);
        }
}
	

