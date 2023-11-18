#include <bits/stdc++.h>
using namespace std;

int N,K;
int a[109];
bool dp[100'009];
int main(){
    cin >> N >> K;
    for (int i=1; i<=K; i++) cin >> a[i];

    for(int i=0; i<=N; i++){
        bool flag = false;
        for(int j=1; j<=K; j++){
            if((i - a[j] >= 0) && (dp[i - a[j]] == false)){
                dp[i] = true;
                flag = true;
            }
        }
        if(flag == false) dp[i] = false;
    }

    if(dp[N]) cout << "First" << endl;
    else cout << "Second" << endl;
    return 0;

}

