#include <bits/stdc++.h>
using namespace std;

int main(){
    int D, N;
    int L[100009], R[100009];
    int up_down[100009];
    int ans[100009];

    cin >> D >> N;
    //参加者はL~Rまで出席
    for(int i=1; i<=N; i++) cin >> L[i] >> R[i];
    for (int i=1; i<=N; i++){
        up_down[L[i]] += 1;
        up_down[R[i]+1] -= 1;
    }

    ans[0] = 0;
    for (int d=1; d<=D; d++) ans[d] = ans[d-1] + up_down[d];
    for (int d=1; d<=D; d++) cout << ans[d] << endl;

    return 0;
}