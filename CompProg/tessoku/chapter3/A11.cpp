#include <bits/stdc++.h>
using namespace std;

//整数xが何番目に存在するか
int N,X;
int A[100009];
int search(int x){
    int L = 1, R = N;
    while(L <= R){
        int M = (L + R) / 2;
        if (x < A[M]) R = M - 1;
        else if (x > A[M]) L = M + 1;
        else return M;
    }
}

int main(){

    cin >> N >> X;
    for(int i=1; i<=N; i++) cin >> A[i];
    // sort (配列, 配列の長さ)　降順の場合はgreater<int>() A[L] ~ A[R-1]までソート
    // sort(A + 1, A + N + 1);

    int ans = search(X);
    cout << ans << endl;
    return 0;

}