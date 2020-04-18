/* 
 * File:   Book.h
 * Author: MonsteR
 *
 * Created on May 17, 2015, 8:52 PM
 */

#ifndef BOOK_H
#define	BOOK_H
#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <string>
#include <string.h>
#include "MyList.h"
using namespace std;
class Book{
    public:
	int bookId;
	int bookPrice;
	char bookName[100];
	int count;
        Book();
        void tokenizer(char *line);
};
class BookDetails{
	map <int, int> bookPrice; //Map to store price corresponding to Book id
        map <int,int> quantitySold;
	int count;
    public:
        char signature;
        BookDetails();
        void insertPrice(const Book *b);
        int fetchPrice(int bookId);
        void insertQuantity(int bookId);
        int fetchQuantity(int bookId);
        void calculateQuantity(int size);
        void getLeastSellingBooks(int size);
};
class BookDetailReader{
	string path;
	fstream input;
	public:
            BookDetailReader(char *);
            void getInput(BookDetails *mBookDetails);
};
#endif	/* BOOK_H */
