#include <bits/stdc++.h>
using namespace std;

string S, T;
int dp[3009][3009];
int N,M;

int main(){
    //最長共通部分列
    // dp[i-1][j], dp[i][j-1], dp[i-1][j-1]+1
    /*
         0 T O K Y O
       0 0 0 0 0 0 0 
       K 0 0 0 1 1 1
       Y 0 0 0 1 2 2 
       O 0 0 1 1 2 3
       T 0 1 1 1 2 3
       O 0 1 2 2 2 3
    */

    cin >> S; N = S.size();
    cin >> T; M = T.size();

    //dp(stringなので0から値は入っている):斜めで採用
    dp[0][0] = 0;
    for(int i=0; i<=N; i++){
        for(int j=0; j<=M; j++){
            //現在の文字同士が一致していれば
            if (i >= 1 && j >=1 && S[i-1] == T[j-1]){
                dp[i][j] = max({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]+1});
            }
            else if(i >=1 && j>=1){
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
            else if(i >=1) dp[i][j] = dp[i-1][j];
            else if(j >=1) dp[i][j] = dp[i][j-1];
        }
    }

    //復元(文字列は0startでdpは1startなので注意)
    vector<int> Answer;
    int i = N-1;
    int j = M-1;
    while (i >= 0 && j >=0){
        if(S[i] == T[j]){
            Answer.push_back(S[i]);
            i--;
            j--;
        }
        else if(dp[i+1][j+1] == dp[i][j+1]){
            i--;
        }
        else if(dp[i+1][j+1] == dp[i+1][j]){
            j--;
        }
    }

    reverse(Answer.begin(), Answer.end());

    for(char a: Answer){
        cout << a;
    }
    cout << endl;
    return 0;

}