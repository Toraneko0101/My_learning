#include <bits/stdc++.h>
using namespace std;

int main(){
    int N,K;
    cin >> N >> K;

    //1 <= N, K <= 9
    int ans = 0;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=K; j++){
            int room = i*100 + j;
            ans += room;
        }
    }
    cout << ans << endl;
}