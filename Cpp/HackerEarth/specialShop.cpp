/* 
https://www.hackerearth.com/practice/algorithms/searching/linear-search/practice-problems/algorithm/special-shop-69904c91/
 */
#include <iostream>

using namespace std;

enum CostPattern{
    decreasing,
    increasing,
    minimum
};

CostPattern getCostPattern(long long cheapPotCount, long long costlyPotCount, long long cheapPotPrice, long long costlyPotPrice){
    long long currentCost = (cheapPotCount * cheapPotCount * cheapPotPrice) + (costlyPotCount * costlyPotCount * costlyPotPrice);
    long long prevCost = ((cheapPotCount-1) * (cheapPotCount-1) * cheapPotPrice) + ((costlyPotCount+1) * (costlyPotCount+1) * costlyPotPrice);
    long long nextCost = ((cheapPotCount+1) * (cheapPotCount+1) * cheapPotPrice) + ((costlyPotCount-1) * (costlyPotCount-1) * costlyPotPrice);
    
    //cout<<"\n"<<currentCost<<"   "<<prevCost<<"   "<<nextCost<<"\n";
    
    if((currentCost < prevCost) && (currentCost > nextCost)){
        return CostPattern::decreasing;
    }else if((currentCost > prevCost) && (currentCost < nextCost)){
        return CostPattern::increasing;
    }

    return CostPattern::minimum;
}

long long findMinCost(long long flowerPotsReq, long long cheapPotPrice, long long costlyPotPrice){
    
    long long cheapPotCount = flowerPotsReq/2;
    long long costlyPotCount = flowerPotsReq-cheapPotCount;
    long long mincheapPotCount = cheapPotCount;
    long long maxcheapPotCount = flowerPotsReq;
    long long minCost = 0;

    while(true){
        CostPattern currentPattern = getCostPattern(cheapPotCount, costlyPotCount, cheapPotPrice, costlyPotPrice);
        if(currentPattern == CostPattern::decreasing){
            mincheapPotCount = cheapPotCount;
            cheapPotCount = (mincheapPotCount + maxcheapPotCount)/2;
            if(mincheapPotCount == cheapPotCount){
                cheapPotCount++;
            }
            costlyPotCount = flowerPotsReq-cheapPotCount;
        }else if(currentPattern == CostPattern::increasing){
            maxcheapPotCount = cheapPotCount;
            cheapPotCount = (mincheapPotCount + maxcheapPotCount)/2;
            costlyPotCount = flowerPotsReq-cheapPotCount;
        }else{
            break;
        }
    }

    minCost = (cheapPotCount * cheapPotCount * cheapPotPrice) + (costlyPotCount * costlyPotCount * costlyPotPrice);
    return minCost;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int testCases;
    cin>>testCases;
    while(testCases--){
        long long flowerPotsReq, typeA, typeB;
        cin>>flowerPotsReq>>typeA>>typeB;
        long long cheapPot = typeA > typeB ? typeB:typeA;
        long long costlyPot = typeA > typeB ? typeA:typeB;
        cout<<findMinCost(flowerPotsReq, cheapPot, costlyPot)<<"\n";
    }

    return 0;
}