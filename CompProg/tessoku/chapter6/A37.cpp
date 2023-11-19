#include <bits/stdc++.h>
using namespace std;
//問題を分割し、各パーツの答えへの寄与分を算出する
long long N, M, B;
long long A[200009];
long long C[200009];
int main(){
    cin >> N >> M >> B;
    for(int i=1; i<=N; i++) cin >> A[i];
    for(int i=1; i<=M; i++) cin >> C[i];
    //Aの道はN個,Cの道はM個
    //何回足されたかを考える
    long long ans = 0;
    for(int i=1; i<=N; i++) ans += (M * A[i]);
    for(int i=1; i<=M; i++) ans += (N * C[i]);
    //右辺の演算の時点でオーバーフローするので注意
    ans += (B * N * M);
    cout << ans << endl;
    return 0;
}