#include <bits/stdc++.h>
using namespace std;
//個数を前計算する
int N;
int A[200009];
long long Sum[109] = {0};
int main(){
    cin >> N;
    for(int i=1; i<=N; i++) cin >> A[i];

    for(int i=1; i<=N; i++){
        Sum[A[i]]++;
    }
    long long ans = 0;
    for(int i=1; i<=100; i++){
        long long buf = Sum[i];
        if(buf <= 2) continue;
        // nC3
        ans += (buf * (buf-1) * (buf-2) / 6);
    }
    cout << ans << endl;
    return 0;
}