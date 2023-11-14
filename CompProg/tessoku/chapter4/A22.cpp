#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    int N;
    ll A[100009], B[100009];
    ll dp[100009];

    cin >> N;
    for(int i=1; i<=N-1; i++) cin >> A[i];
    for(int i=1; i<=N-1; i++) cin >> B[i];

    dp[1] = 0;
    //dp:最後の行動がもらえてないので、配る方だと面倒くさい
    //毎回決まっただけ増えるわけでもないので
    for(int i=2; i<=N-1; i++){
        dp[i] = -1'000'000'000;
    }
    //例。
    //i=1 A[i]=2, max(dp[2],dp[1]+100)
    //i=2 A[i]=4, max(dp[4],dp[2]+100)
    //i=3 A[i]=4, max(dp[4],dp[3]+100)
    //3の初期化されていないスコアを採用しないためにマイナスで初期化する。
    //3は一度もたどり着いていないので+100は、スコアの最大値として採用できない 
    for(int i=1; i<=N-1; i++){
        dp[A[i]] = max(dp[A[i]], dp[i] + 100);
        dp[B[i]] = max(dp[B[i]], dp[i] + 150);
    }

    cout << dp[N] << endl;
    return 0;
}