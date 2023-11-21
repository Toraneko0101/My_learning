#include <bits/stdc++.h>
using namespace std;

int N,K;
int A[309], B[309];
int AB[109][109] = {0};
int S[109][109] = {0};
int main(){
    cin >> N >> K;
    for(int i=1; i<=N; i++){
        cin >> A[i] >> B[i];
        AB[A[i]][B[i]] ++;
    }

    //累積和(i,jまでの値がS[i][j])
    for (int i=0; i<=100; i++){
        for(int j=1; j<=100; j++){
            S[i][j] = S[i][j-1] + AB[i][j];
        }
    }

    for(int i=1; i<=100; i++){
        for(int j=0; j<=100; j++){
            S[i][j] = S[i-1][j] + S[i][j];
        }
    }

    int ans = 0;
    //体力がi,気力がjとして、K*Kの面積に存在しているか:計算量100**2
    for(int i=1; i<=100; i++){
        for(int j=1; j<=100; j++){
            int top = max(i-K-1, 0);
            int left = max(j-K-1, 0);
            int bottom_right = S[i][j];
            int top_left = S[top][left];
            int top_right = S[top][j];
            int bottom_left = S[i][left];
            int buf_ans = bottom_right + top_left - top_right - bottom_left;
            ans = max(ans, buf_ans);
        }
    }

    cout << ans << endl;
}