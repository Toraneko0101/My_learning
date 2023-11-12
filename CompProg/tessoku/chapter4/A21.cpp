#include <bits/stdc++.h>
using namespace std;

int N;
int P[2009], A[2009];
int dp[2009][2009] = {0};
int main(){
    //dp[l][r] l~r番目のblock現存
    cin >> N;
    for(int i=1; i<=N; i++) cin >> P[i] >> A[i];

    // dp[l-1][r]から左端を除く  l <= P_{l-1} <= r なら加点
    //dp[l][r+1]から右端を除く   l <= P_{r+1} <= r なら加点    
    // l=1,r=Nからstart。l=rになったら終了。l < rはありえないので調べない
    //右からとっていくpatternと、左からとっていくpatternで最大を取得
    // l=2, r=3の場合、 dp[1][3]とdp[2][4]が可能性あり。dp[1][3]については前のループで取得済み
    for(int l=1; l<=N; l++){
        for(int r=N; r>=l; r--){
            if(l==1 && r==N) continue;

            if(l > 1){
                dp[l][r] = max(dp[l][r], dp[l-1][r] + A[l-1] * (l <= P[l-1] && P[l-1] <= r));
            }
            if (r < N){
                dp[l][r] = max(dp[l][r], dp[l][r+1] + A[r+1] * (l <= P[r+1] && P[r+1] <= r));
            }
                
        }
    }
    int Answer = 0;
    for(int i=1; i<=N; i++) Answer = max(Answer, dp[i][i]);    
    cout << Answer << endl;
    return 0;
}