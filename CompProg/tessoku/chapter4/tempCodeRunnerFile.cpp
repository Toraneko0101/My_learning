#include <bits/stdc++.h>
using namespace std;

int N;
int H[10009];
int dp[10009];

int main(){
    cin >> N;
    for(int i=1; i<=N; i++) cin >> H[i];
    dp[1] = 0;
    dp[2] = H[2] - H[1];
    for(int i=3; i<=N; i++){
        dp[i] = min(dp[i-1] + abs(H[i]-H[i-1]), dp[i-2] + abs(H[i]-H[i-2]));
    }

    cout << dp[N] << endl;
    return 0;
}