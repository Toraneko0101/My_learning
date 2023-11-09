// 二次元累積和
#include <bits/stdc++.h>
using namespace std;

int H,W,Q;
int X[1509][1509], S[1509][1509];
int A[100009];
int B[100009];
int C[100009];
int D[100009];

int main(){
    //初期化
    cin >> H >> W;
    for (int i = 1; i<=H; i++){
        for (int j = 1; j<=W; j++){
            cin >> X[i][j];
        }
    }
    cin >> Q;
    for (int i=1; i<=Q; i++) cin >> A[i] >> B[i] >> C[i] >> D[i];

    //配列Sの初期化
    for (int i=0; i<=H; i++){
        for (int j=0; j<=W; j++){
            S[i][j] = 0;
        }
    }

    //横の累積和
    for(int i=0; i<=H; i++){
        for (int j=1; j<=W; j++) S[i][j] = S[i][j-1] + X[i][j];
    }

    //縦の累積和
    for (int i=1; i<=H; i++){
        for (int j=0; j<=W; j++) S[i][j] = S[i-1][j] + S[i][j];
    }

    //ans(相殺) 右下 - 右上(y-1) - 左下(x-1) + 左上(x-1,y-1)
    for (int i=1; i<=Q; i++){
        cout << S[C[i]][D[i]] + S[A[i]-1][B[i]-1] - S[A[i]-1][D[i]] - S[C[i]][B[i]-1] << endl;
    }

    return 0;
}