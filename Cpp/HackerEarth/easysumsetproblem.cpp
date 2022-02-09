/* 
https://www.hackerearth.com/practice/algorithms/searching/linear-search/practice-problems/algorithm/easy-sum-set-problem-7e6841ca/
 */

#include <iostream>
#include <vector>

using namespace std;

int getMaxofArr(vector<int>& inputVec){
    int max = inputVec[0];
    for(unsigned long i=1; i<inputVec.size(); i++){
        if(inputVec[i] > max){
            max = inputVec[i];
        }
    }

    return max;
}

int getMinofArr(vector<int>& inputVec){
    int min = inputVec[0];
    for(unsigned long i=1; i<inputVec.size(); i++){
        if(inputVec[i] < min){
            min = inputVec[i];
        }
    }
    return min;
}

void printsetB(vector<int> &setA, vector<int> &setC){
    int *diffMap = new int[101]; //Since element in set C cannot be greater than 100
    int *setCMap = new int[101];
    for(int i=0; i<101; i++){
        diffMap[i] = 0;
        setCMap[i] = 0;
    }

    int minB = getMinofArr(setC) - getMinofArr(setA);
    int maxB = getMaxofArr(setC) - getMaxofArr(setA);
    
    vector<int>::iterator it = setC.begin();
    for(; it != setC.end(); it++){
        setCMap[*it] = 1;
    }

    for(int i=minB; i<= maxB; i++){
        vector<int>::iterator itA = setA.begin();
        bool belongsToSet = true;
        for(;itA != setA.end(); itA++){
            int sum = *itA + i;
            if(setCMap[sum] != 1){
                belongsToSet = false;
                break;
            }
        }
        if(belongsToSet == true){
            diffMap[i] = 1;
        }
    }

    // vector<int>::iterator it = setC.begin();
    // for(; it != setC.end(); it++){
    //     vector<int>::iterator itA = setA.begin();
    //     for(;itA != setA.end(); itA++){
    //         int diff = *it-*itA;
    //         if(diff > 0 && diffMap[diff] != 1){
    //             diffMap[diff] = 1;
    //         }
    //     }
    // }

    for(int i=0; i<101; i++){
        if(diffMap[i] > 0){
            cout<<i<<" ";
        }
    }
}

int main(){
    int sizeA, sizeC;
    vector<int>setA;
    vector<int>setC;
    cin>>sizeA;
    for(int i=0; i<sizeA; i++){
        int input;
        cin>>input;
        setA.push_back(input);
    } 
    
    cin>>sizeC;
    for(int i=0; i<sizeC; i++){
        int input;
        cin>>input;
        setC.push_back(input);
    }

    printsetB(setA, setC);
    return 0;
}