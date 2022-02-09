/*
Question Url: https://www.hackerearth.com/practice/algorithms/searching/linear-search/practice-problems/algorithm/yet-another-easy-problem-1f3273a0/
*/

#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int gcd(int x, int y){
    int a, b, r;
    if(x > y){
        a = x;
        b = y;
    }
    else{
        a = y;
        b = x;
    }
    while(b != 0){
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int getHexSum(int number){
	int hexSum = 0;
    while(number){
        hexSum = hexSum + (number%16);
        number = number/16;
    }
	return hexSum;
}

bool isGCDGreaterThanOne(int number){
	if(number > 1){
		int hexSum = getHexSum(number);
		if(__gcd(number, hexSum) > 1){
			return true;
		}
	}
	return false;
}
int getNumbersCount(int lowerLimit, int upperLimit){
	int gcdGreaterThanOneCount = 0;
    for(int i=lowerLimit; i<=upperLimit; i++){
		if(isGCDGreaterThanOne(i)){
            gcdGreaterThanOneCount++;
        }
	}
    return gcdGreaterThanOneCount;
}

int main() {
	int testCase;
	cin>>testCase;
	for(int i=0; i<testCase; i++){
		int lowerLimit, upperLimit;
		cin>>lowerLimit>>upperLimit;
		cout<<getNumbersCount(lowerLimit, upperLimit)<<"\n";
	}
}
