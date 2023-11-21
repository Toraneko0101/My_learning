#include <bits/stdc++.h>
using namespace std;

int N;
char S[200009];
int main(){
    cin >> N;
    for(int i=1; i<=N; i++) cin >> S[i];

    //p,p+1,p+2が同じ色であるときを考える
    //左から塗ることで、p-1以下の色が確定
    //右から塗ることで、p+3より右の色が確定
    //最後にp~p+2を塗る

    bool ans = false;
    for(int i=1; i<=N-2; i++){
        if(S[i] == S[i+1] && S[i+1] == S[i+2]) ans = true;
    }
    if(ans) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}