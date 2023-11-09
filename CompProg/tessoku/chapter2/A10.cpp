#include <bits/stdc++.h>
using namespace std;

int main(){
    int N, D;
    int A[100009], front_max[100009], back_max[100009];
    int L[100009], R[100009];
    //d日目は l ~ rが使えない
    //よって、l-rとr+1からの最大値
    //逆順も必要ということ？
    
    //入力
    cin >> N;
    for(int i=1; i<=N; i++) cin >> A[i];
    cin >> D;
    for (int i=1; i<=D; i++) cin >> L[i] >> R[i];

    //先頭max
    front_max[1] = A[1];
    for (int i=2; i<=N; i++) front_max[i] = max(front_max[i-1], A[i]);
    //逆順max
    back_max[N] = A[N];
    for (int i=N-1; i>=1; i--) back_max[i] = max(back_max[i+1], A[i]);

    //ans(条件により末尾まで使えないことはない)
    for(int i=1; i<=D; i++){
        cout << max(front_max[L[i] - 1], back_max[R[i] + 1]) << endl;
    }
    return 0;
}