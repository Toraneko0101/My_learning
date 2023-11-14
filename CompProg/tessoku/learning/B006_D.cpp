// トランプ挿入ソート
#include <bits/stdc++.h>
using namespace std;
// LIS?
int N;
int C[30009];
int dp[30009];
int L[30009];
int LEN = 0;
//LEN=iの時は何回の操作で並べられるか
//既にLEN個昇順に並んでいるので、N - LENするだけ
int main(){
    cin >> N;
    for(int i=1; i<=N; i++) cin >> C[i];

    //一つずつpushして、二分探索する
    for(int i=1; i<=N; i++){
        int pos = lower_bound(L+1,L+LEN+1, C[i]) - L;

        dp[i] = pos; //カードがi枚までの時、iを入れて、幾つ昇順に並んでいるか
        L[dp[i]] = C[i];

        if(dp[i] > LEN) LEN += 1; //N枚の中の最長昇順部分列

    }

    cout << N - LEN << endl;
}
