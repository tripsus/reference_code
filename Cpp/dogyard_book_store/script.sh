#!/bin/bash
output="knowlarity"
g++ -Wall -c MyList.cpp
ls
g++ -Wall -c MyList.o Book.cpp 
ls
g++ -Wall -c Customer.cpp
g++ -Wall -c main.cpp 
g++ -Wall MyList.o Book.o Customer.o main.o -o $output
echo 
echo "###### Executable prepared with name $output ##########"

