#include <bits/stdc++.h>
using namespace std;

//最長増加部分列問題(増加部分列のうち最長のものを求める)
int N;
int A[100009];
int dp[100009];
int L[100009];
int LEN = 0; //最長部分列

int main(){
    cin >> N;
    for(int i=1; i<=N; i++) cin >> A[i];
    //長さxの部分列のうち、最後の要素が最小のものをL[x]として管理する
    // L[x] < A[i]であれば,dp[i]はx+1となる。つまりL[x] < A[i]を満たす境界(idx)kを求めたい
    // Lは単調増加なので、これを満たすものは二分探索で求められる

    for (int i=1; i<=N; i++){
        int x = lower_bound(L+1, L+LEN+1, A[i]) - L; //L(x)以上のidxを返す L[1] ~ L[LEN+1]
        dp[i] = x; //最後の要素がA[i]の最長部分列は、長さx

        //配列Lを更新:今回の最長部分列の結果を受け
        //　例
        // L[1] = 4, L[2] = 6, 今回5なら L[2] = 5で上書き 7なら、L[3] = 7となる
        // L[1] = 1 今回1なら L[1] = 1で上書き。lower_boundで以上を取っているので、L[dp[i]]の値が増えることはない
        L[dp[i]] = A[i];
        //もし最長部分列が更新されたら
        if(dp[i] > LEN) LEN += 1;
    }

    cout << LEN << endl;
    return 0;
}