/* 
https://www.hackerearth.com/practice/algorithms/searching/linear-search/practice-problems/algorithm/joker-and-thieves-53e59f4a/
*/
#include<bits/stdc++.h>
using namespace std;
char POLICE_MAN = 'P';
char THIEF = 'T';
char CAUGHT_THIEF = 'A';
int NO_THIEF = -1;

int getThiefIndex(vector<char> &A, int K, int N, int pi){
    int left_limit = pi-K;
    int right_limit = pi+K;
    if(left_limit < 0){
        left_limit = 0;
    }
    if(right_limit > N){
        right_limit = N;
    }
    for(int i=left_limit; i<=right_limit; i++){
        if(A[i] == THIEF){
            A[i] = CAUGHT_THIEF;
            return i;
        }
    }
    return NO_THIEF;
}
int solution (vector<vector<char> > A, int K, int N) {
   int total_count = 0;
   if(K >= N){
        for(int i=0; i<N; i++){
            int row_police_count = 0;
            int row_thief_count = 0;
            for(int j=0; j<N; j++){
                if(A[i][j] == POLICE_MAN){
                    row_police_count ++;
                }else{
                    row_thief_count++;
                }
            }
            if(row_thief_count<row_police_count){
                total_count += row_thief_count;
            }else{
                total_count += row_police_count;
            }
        }
   }else{
        for(int i=0; i<N; i++){
            int prev_ti = 0;
            for(int j=0; j<N; j++){
                if(A[i][j]==POLICE_MAN){
                    int thief_index = getThiefIndex(A[i], K, N-1, j);
                    if(thief_index != -1){
                        total_count += 1;
                        prev_ti = thief_index;
                    }
                }
            }
            //cout<<total_count<<"\n";
        }
    }
    return total_count;
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for(int t_i=0; t_i<T; t_i++)
    {
        int N;
        cin >> N;
        int K;
        cin >> K;
        vector<vector<char> > A(N, vector<char>(N));
        for (int i_A=0; i_A<N; i_A++)
        {
        	for(int j_A=0; j_A<N; j_A++)
        	{
        		cin >> A[i_A][j_A];
        	}
        }

        int out_;
        out_ = solution(A, K, N);
        cout << out_;
        cout << "\n";
    }
}