#include <bits/stdc++.h>
using namespace std;
using Int = long long;

Int N, W, v[109], w[109];
Int dp[109][100009];

int main(){
    //重さ-w, 価値v
    cin >> N >> W;
    for (int i=1; i<=N; i++) cin >> w[i] >> v[i];
    for (int i=0; i<=N; i++){
        for(int j=0; j<=W; j++) dp[i][j] = -1'000'000'000'000LL; //価値が不用意に上回らないように(dpする際に場合分けしたくないので)
    }

    //dp
    dp[0][0] = 0;
    for(int i=1; i<=N; i++){
        for(int j=0; j<=W; j++){
            if(j < w[i]) dp[i][j] = dp[i-1][j];
            else dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]] + v[i]); //重さをw[i]だけプラスしてv[i]の価値を加える
        }
    }

    Int Answer = 0;
    for(int i=0; i<=W; i++) Answer = max(Answer, dp[N][i]);
    cout << Answer << endl;
    return 0;
}