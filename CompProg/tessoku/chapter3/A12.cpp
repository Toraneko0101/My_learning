#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll N,K;
ll A[100009];

//x秒後までに印刷済みか
bool check(long long x){
    ll sum = 0;
    for (int i=1; i<=N; i++) sum += x / A[i];
    if(sum >=K) return true;
    return false;
}

int main(){
    cin >> N >> K;
    for (int i=1; i<=N; i++) cin >> A[i];

    //二分探索
    ll Left = 1, Right = 1'000'000'000;
    while (Left < Right){
        ll Mid = (Left + Right) / 2;
        bool ans = check(Mid);
        if(ans) Right = Mid;    //答えはMid以下(>=なので)
        else Left = Mid + 1;    //答えはMid+1以上(Leftは満たしていない)
    }

    cout << Left << endl;
    return 0;
}