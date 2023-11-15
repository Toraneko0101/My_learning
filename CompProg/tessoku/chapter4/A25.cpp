#include <bits/stdc++.h>
using namespace std;

int H,W;
string C[39];
long long dp[39][39] = {0};
long long ans = 0;
int main(){
    cin >> H >> W;
    for (int i=1; i<=H; i++) cin >> C[i];

    //上と左からの足し算。デフォルト0。-1なら1とmaxして足さない
    for (int i=1; i<=H; i++){
        for(int j=1; j<=W; j++){
            if(i==1 && j==1){
                dp[i][j] = 1;
                continue;
            }
            //それぞれ足していく
            if (C[i][j-1] == '.'){
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
                //cout << dp[i][j] << endl;
            }
        }
    }
    cout << dp[H][W] << endl;
    return 0;

}