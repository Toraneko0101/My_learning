#include <bits/stdc++.h>
using namespace std;

//局所探索法
/**
 * 1. 初期解をランダムに生成
 * 2. 小さな変更をランダムに行い、スコアがよくなれば採用する
 * 
 * 最小二乗法なら良く試した覚えがある
*/

//入力値等
int N, X[159], Y[159];
int P[159]; //都市を訪れる順番の情報

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
int main(){
    //rand + xorshift32
    initrand();

    //入力
    cin >> N;
    for(int i=1; i<=N; i++) cin >> X[i] >> Y[i];

    //初期解
    P[1] = 1, P[N+1] = 1;
    for(int i=2; i<=N; i++) P[i] = i;

    //山登り法
    double CurrentScore = GetScore();
    for(int t=1; t<=200000; t++){
        //ランダムに反転させる区間を選ぶ
        long long L = xorshift32(2, N);
        long long R = xorshift32(2, N);
        if(L > R) swap(L, R);

        //reverseで反転
        reverse(P+L, P+R+1);
        double NewScore = GetScore();

        if(CurrentScore >= NewScore) CurrentScore = NewScore; //改善すればスコアを更新
        else reverse(P+L, P+R+1); //改善しなければ元に戻す
    }

    for(int i=1; i<=N+1; i++) cout << P[i] << endl;
    return 0;
}