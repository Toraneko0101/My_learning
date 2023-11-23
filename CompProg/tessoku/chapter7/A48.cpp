#include <bits/stdc++.h>
using namespace std;

int N, X[159], Y[159];
int P[159];

//乱数の初期化
void initrand(){
    srand((unsigned int)time(NULL));
}

//乱数 a~b
long long xorshift32(long long a, long long b){
    unsigned int x = rand();
    long long ans;
    //xorshift32
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    ans = a + x % (b - a + 1);
    return ans;
}

//都市p,qの間の距離
double GetDistance(int p, int q){
    return sqrt(pow(X[p] - X[q] , 2) + pow(Y[p] - Y[q] , 2));
}


//スコアの計算
double GetScore(){
    double sum = 0;
    for(int i=1; i<=N; i++) sum += GetDistance(P[i], P[i+1]);
    return sum;
}

//焼きなまし法

/**
 * 一定の確率でスコアを悪化させる変更を許す。
 * 偽の最適解対策
 * スコアの落差(Δ)が大きいほど採用確率pを下げる
 * p = {
 *      1 : スコア改善する場合
 *      e^(-Δ/t) : スコア悪化する場合
 * }
 * Tは温度と呼ばれるparam
 * 
 * 序盤：偽の最適解から脱出しやすいように悪化を許す確率を高めに
 * 終盤：真の最適解に近づきやすいように悪化を許す確率を低めに
*/



// 0 ~ 1のrandamな実数を返す
double Randouble(){
    return 1.0 * rand() / RAND_MAX;
}

int main(){
    initrand();
    cin >> N;
    for(int i=1; i<=N; i++) cin >> X[i] >> Y[i];

    //初期解
    P[1] = 1, P[N+1] = 1;
    for(int i=2; i<=N; i++) P[i] = i;

    //焼きなまし法
    double CurrentScore = GetScore();
    for(int t=1; t<=200000; t++){
        long long L = xorshift32(2, N);
        long long R = xorshift32(2, N);
        if(L > R) swap(L, R);
        reverse(P + L, P + R + 1);
        double NewScore = GetScore();

        //採用確率probability
        double T = 30.00 - 28.00 * t / 200000.0; //徐々に温度を下げる
        //np.exp(0) = 1;
        double Probability = exp(min(0.0, (CurrentScore - NewScore) / T));
        if(Randouble() < Probability) CurrentScore = NewScore;
        else reverse(P+L, P+R+1);
    }

    //出力
    for(int i=1; i<=N+1; i++) cout << P[i] << endl;
    return 0;
}