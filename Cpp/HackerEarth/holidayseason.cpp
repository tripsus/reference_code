#include <iostream>
#include <vector>

using namespace std;

int getNextOccurence(int curOccurence, vector<char> &alphabets){
    char curChar = alphabets[curOccurence];
    
}

int main(){
    int size;
    vector<char> alphabets;
    int solutionCount = 0;
    
    cin>>size;

    for(int i=0; i<size; i++){
        char temp;
        cin>>temp;
        alphabets.push_back(temp);
    }
    for(int i=0; i<size-3; i++){
        int nextA = getNextOccurence(i, alphabets);
    }
}