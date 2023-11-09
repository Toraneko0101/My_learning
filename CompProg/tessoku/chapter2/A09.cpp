#include <bits/stdc++.h>
using namespace std;

int H, W, N;
int A[100009];
int B[100009];
int C[100009];
int D[100009];

int up_down[1509][1509], S[1509][1509] = {0};

int main(){
    cin >> H >> W >> N;
    for(int i=1; i<=N; i++) cin >> A[i] >> B[i] >> C[i] >> D[i];
    for(int i=1; i<=N; i++){
        up_down[A[i]][B[i]] += 1;
        up_down[C[i]+1][B[i]] -= 1;
        up_down[A[i]][D[i]+1] -= 1;
        up_down[C[i]+1][D[i]+1] += 1;
    }
    //横加算
    for (int i=0; i<=H; i++){
        for (int j=1; j<=W; j++){
            S[i][j] = S[i][j-1] + up_down[i][j];
        }
    }
    //縦加算
    for(int i=1; i<=H; i++){
        for (int j=0; j<=W; j++){
            S[i][j] = S[i-1][j] + S[i][j];
        }
    }
    //ans
    for (int i=1; i<=H; i++){
        for (int j =1; j<=W; j++){
            if(j>=2) cout << " ";
            cout << S[i][j];
        }
        cout << endl;
    }
    return 0;
}