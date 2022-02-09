/* 
https://www.hackerearth.com/practice/algorithms/searching/linear-search/practice-problems/algorithm/maximum-sum-4-f8d12458/
 */

#include <iostream>
#include <vector>

using namespace std;

int main(){
    long long arrSize;
    cin>>arrSize;
    vector<long long> arrElements;
    for(long long i=0;i<arrSize; i++){
        long long num;
        cin>>num;
        arrElements.push_back(num);
    }
    long long minNegative = INT64_MIN;
    long long maxSum = 0, maxSumElememntCount = 0;
    for(long long i=0; i<arrSize; i++){
        if(arrElements[i] < 0){
            if(arrElements[i] > minNegative){
                minNegative = arrElements[i];
            }
        }else{
            maxSum += arrElements[i];
            maxSumElememntCount++;
        }
    }

    if(maxSumElememntCount > 0){
        cout<<maxSum<<" "<<maxSumElememntCount;
    }else{
        cout<<minNegative<<" "<<1;
    }   
}