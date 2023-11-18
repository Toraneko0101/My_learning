#include <bits/stdc++.h>
using namespace std;

int N;
int A[2009];
int dp[2009][2009];
int main(){
    //動的計画法
    //最上段をdp[1][1]とする
    //末尾から考え、遡っていくことで解を導く
    //iが奇数の時は、太郎の操作
    //iが偶数の時は、次郎の操作
    cin >> N;
    for(int i=1; i<=N; i++) cin >> A[i];

    //N段目
    for(int i=1; i<=N; i++) dp[N][i] = A[i];

    //N-1 ~ 1
    for(int i=N-1; i>=1; i--){
        //横の長さはiまで
        for(int j=1; j<=i; j++){
            //次郎
            if(i % 2 == 0) dp[i][j] = min(dp[i+1][j], dp[i+1][j+1]);
            //太郎
            if(i % 2 == 1) dp[i][j] = max(dp[i+1][j], dp[i+1][j+1]);
        }

    }
        cout << dp[1][1] << endl;
        return 0;
}