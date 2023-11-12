#include <bits/stdc++.h>
using namespace std;

string S, T;
int dp[2009][2009];
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

    //dp(stringなので0から値は入っている)
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

    cout << dp[N][M] << endl;
    return 0;
}