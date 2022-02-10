// https://leetcode.com/problems/longest-substring-without-repeating-characters/

#include <iostream>
#include <string>

using namespace std;

int lengthOfLongestSubstring(string s) {
int inpLength = s.length();
    int curMaxlength = 0;
    int overallMaxLength = 0;
    int charIdx[128];
    for(int i=0; i<128; i++){
        charIdx[i] = -1;
    }

    for(int i=0; i<inpLength; i++){
        char curChar = s.at(i);
        if(charIdx[curChar-' '] != -1){
            if(curMaxlength > overallMaxLength){
                overallMaxLength = curMaxlength;
            }
            int prevIdx = charIdx[curChar-' '];
            charIdx[curChar-' '] = i;
            curMaxlength = i - prevIdx;
            for(int j=prevIdx-1; j>=0; j--){
                if(charIdx[s.at(j)-' '] < prevIdx){
                    if(charIdx[s.at(j) - ' '] == -1){
                        break;
                    }
                    charIdx[s.at(j) - ' '] = -1;
                }

            }
        }else{
            curMaxlength++;
            charIdx[curChar-' '] = i;
        }
    }
    if(curMaxlength > overallMaxLength){
        overallMaxLength = curMaxlength;
    }
    return overallMaxLength;
    }
}


int main(){
    string input;
    cin>>input;
    cout<<lengthOfLongestSubstring(input);
    return 0;
}