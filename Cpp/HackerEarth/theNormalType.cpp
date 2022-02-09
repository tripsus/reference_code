/*
https://www.hackerearth.com/practice/algorithms/searching/linear-search/practice-problems/algorithm/the-normal-type/ 
*/

#include <iostream>
#include <map>
#include <vector>

using namespace std;

int getNuxOccurence(map<int, vector<int>> &occurenceMap, int num, int lastOccur){
    vector<int> occArr = occurenceMap[num];
    for(size_t i=0; i<occArr.size(); i++){
        if(occArr[i]>lastOccur){
            return occArr[i];
        }
    }
    return -1;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int size, lastNum;
    long long answer = 0;
    cin>>size;
    int *inputArr = new int[size];
    map<int, vector<int>> occurenceMap;

    for(int i=0; i<size; i++){
        int temp;
        cin>>temp;
        inputArr[i] = temp;
    }

    for(int i=0; i<size; i++){
        int curNum = inputArr[i];
        if(occurenceMap.find(curNum) == occurenceMap.end()){
            vector<int> arr;
            arr.push_back(i);
            occurenceMap[curNum] = arr;
            lastNum = curNum; 
        }else{
            occurenceMap[curNum].push_back(i);
        }
    }

    int lastIndex = occurenceMap[lastNum][0];
    answer = answer + size-lastIndex;
    if(lastNum == inputArr[0]){
        answer = (long long)size * (long long)(size+1)/2;
        cout<<answer;
    }else{
        for(int i=1; i<size; i++){
        int lastNum = inputArr[i-1];
        int nextOccurence = getNuxOccurence(occurenceMap, lastNum, i-1);
        if(nextOccurence == -1){
            cout<<answer;
            break;
        }else{
            if(lastIndex < nextOccurence){
                lastIndex = nextOccurence;
            }
            answer = answer + size-lastIndex;
        }
    }
    //cout<<answer;
    }
    
    
}