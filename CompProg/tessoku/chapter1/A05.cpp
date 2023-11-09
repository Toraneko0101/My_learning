#include <bits/stdc++.h>
using namespace std;

int N, K, ans = 0;

int main(){
    cin >> N >> K;
    for (int i=1; i<=N; i++){
        for (int j=1; j<=N; j++){
            int k = K - i - j;
            if (1 <= k  && k <= N) ans++;
        }
    }

    cout << ans << endl;
    return 0;
}