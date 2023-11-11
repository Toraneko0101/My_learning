#include <bits/stdc++.h>
using namespace std;


int N, K;
int A[1009], B[1009], C[1009], D[1009];
int P[1000009], Q[1000009];

int main(){
    cin >> N >> K;
    for (int i = 1; i<=N; i++) cin >> A[i];
    for (int i = 1; i<=N; i++) cin >> B[i];
    for (int i = 1; i<=N; i++) cin >> C[i];
    for (int i = 1; i<=N; i++) cin >> D[i];

    //a.b
    for (int i=1; i<=N; i++){
        for (int j=1; j<=N; j++){
            P[(i-1)*N + j] = A[i] + B[j];
        }
    }
    //c,d
    for (int i=1; i<=N; i++){
        for (int j=1; j<=N; j++){
            Q[(i-1)*N + j] = C[i] + D[j];
        }
    }

    //qのsort
    sort(Q+1, Q+(N*N)+1);

    //lower_bound(以上)
    for(int i=1; i<=N*N; i++){
        //pointer同士の引き算でint型のidxに
        int pos = lower_bound(Q+1, Q+(N*N)+1, K - P[i]) - Q;

        //満たさないケースを考慮
        if(pos <= N*N && Q[pos] == K - P[i]){
            cout << "Yes" << endl;
            return 0;
        }

    }
    cout << "No" << endl;
    return 0;
}