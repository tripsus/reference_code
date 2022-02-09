/*
https://leetcode.com/problems/perfect-squares/
*/

#include<iostream>
#include<vector>
#include <cmath>

using namespace std;

int numSquares(int n) {
    vector <int> perfectSquares(n+1,0);
    
    for(size_t i=0; i<=n; i++){
        perfectSquares[i] = i;
    }

    int squareIndex = 2;
    int perfectSquareValue = squareIndex*squareIndex;

    while(perfectSquareValue <= n){
        perfectSquares[perfectSquareValue] = 1;
        for(int i=perfectSquareValue+1; i<=n ; i++){
            int minCount = 0;
            int remainder = i-perfectSquareValue;
            minCount = perfectSquares[perfectSquareValue];
            minCount += perfectSquares[remainder];
            if(minCount < perfectSquares[i]){
                perfectSquares[i] = minCount;
            }
        }
        squareIndex++;
        perfectSquareValue = squareIndex*squareIndex;
    }

    return perfectSquares[n];
}


int main(){
    int n;
    cin>>n;
    cout<<numSquares(n);
    return 0;
}