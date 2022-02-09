/* 
https://www.hackerearth.com/practice/algorithms/searching/linear-search/practice-problems/algorithm/counting-frog-paths-1abd84d5/
 */

#include <iostream>
#include <vector>

using namespace std;

void markTravelledPosition(int curXCord, int curYCord, int initXCord, int initYCord, int squareSize,int timeRemaining, vector<vector<int> >&squarePositions){
    if(timeRemaining == -1 || squarePositions[curXCord-initXCord][curYCord-initYCord] == 1){
        return;
    }

    int maxXCord = initXCord + squareSize;
    int maxYCord = initYCord + squareSize;

    squarePositions[curXCord-initXCord][curYCord-initYCord] = 1;
    
    if(curXCord < maxXCord){
        markTravelledPosition(curXCord+1, curYCord, initXCord, initYCord, squareSize, timeRemaining-1, squarePositions);
    }
    if(curYCord < maxYCord){
        markTravelledPosition(curXCord, curYCord+1, initXCord, initYCord, squareSize, timeRemaining-1, squarePositions);
    }
}


int getPossiblePositionCount(int xCord, int yCord, int squareSize, int time){
    int timeTakenToReachSquareOrigin = xCord + yCord;
    int timeRemaining = time - timeTakenToReachSquareOrigin;
    if(timeRemaining < 0){
        return 0;
    }
    vector<vector<int> > squarePositions (timeRemaining+1, vector<int>(timeRemaining+1));

    for(unsigned long i=0; i<squarePositions.size(); i++){
        for(unsigned long j=0; j<squarePositions[i].size(); j++){
            squarePositions[i][j] = 0;
        }
    }
    markTravelledPosition(xCord, yCord, xCord, yCord, squareSize, timeRemaining, squarePositions);
    int positionsCount = 0;
    for(unsigned long i=0; i<squarePositions.size(); i++){
        for(unsigned long j=0; j<squarePositions[i].size(); j++){
            if (squarePositions[i][j] == 1){
                positionsCount++;
            }
        }
    }
    return positionsCount;
}

int main(){
    int xCord, yCord, squareSize, time;
    cin>>xCord;
    cin>>yCord;
    cin>>squareSize;
    cin>>time;
    
    cout<<getPossiblePositionCount(xCord,yCord,squareSize,time);
    return 0;
}