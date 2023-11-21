#include <bits/stdc++.h>
using namespace std;

//不変量に着目する
int N;
char C;
char A[200009];
int main(){
    cin >> N >> C;
    int color = -1;
    if(C == 'W') color = 0;
    else if(C == 'B') color = 1;
    else if(C == 'R') color = 2;
    for(int i=1; i<=N; i++) cin >> A[i];
    //白を0,青を1,赤を2とする。この時の3で割った余りは操作を行っても変わらない
    //N-1回の操作で、カードは1枚になるが、その際の色を調べたい
    int ans = 0;
    for(int i=1; i<=N; i++){
        if(A[i] == 'R') ans += 2;
        if(A[i] == 'B') ans += 1; 
    }
    if(ans % 3 == color) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}