/*
Question Url: https://www.hackerearth.com/practice/algorithms/searching/linear-search/practice-problems/algorithm/almost-golden-rectangular-1c9d72c0/
*/
#include <iostream>

using namespace std;

int main(){
    int testCase, goldenRectangleCount = 0;
    
    cin>>testCase;

    while(testCase--){
        int width, height;
        cin>>width>>height;
        double ratio = (double)width/height;
        if(ratio >= 1.6 && ratio <= 1.7){
            goldenRectangleCount++;
        }
    }
    cout<<goldenRectangleCount<<"\n";

}