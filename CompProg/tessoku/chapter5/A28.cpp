#include <bits/stdc++.h>
using namespace std;

//+,-,*ならどのタイミングで余りをとっても良い
int N, A[100009];
char T[100009];
int ans = 0;

int main(){
    cin >> N;
    for(int i=1; i<=N; i++) cin >> T[i] >> A[i];
    for(int i=1; i<=N; i++){
        if(T[i] == '+') ans += A[i];
        else if(T[i] == '-') ans -= A[i];
        else if(T[i] == '*') ans *= A[i];
        //負の数になったとき用(黒板の数は負にならないはずなので)
        if(ans < 0) ans += 10000;

        ans %= 10000;
        cout << ans << endl;

    }

    return 0;
}