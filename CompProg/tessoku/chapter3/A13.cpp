#include <bits/stdc++.h>
using namespace std;

int N, K , A[100009], R[100009];

//尺取り法。R_{n+1} > R_{n} O(N)でいける
// R[i]はどこまでの差分がK以下か
int main(){
    cin >> N >> K;
    for(int i=1; i<=N; i++) cin >> A[i];

    for (int i=1; i<=N; i++){
        if(i == 1) R[i] = 1;
        else R[i] = R[i-1]; //ひとつ前のところまでは確実に満たす
        //R[i]がidxを満たし、なおかつ差分がK以下なら
        while (R[i] < N && A[R[i] + 1] - A[i] <= K){
            R[i] += 1;
        }
    }

    long long ans = 0;
    //自身以下も含んでいるので
    for (int i=1; i<=N; i++) ans += (R[i] - i);
    cout << ans << endl;
    return 0;
}