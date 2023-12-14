#include <bits/stdc++.h>
using namespace std;

std::string Str_length(int a, int b, long long k, vector<vector<long long>> &dp){
    if(a == 0){
        //b個分のbが返る
        return string(b, 'b');
    }
    if(b == 0){
        return string(a, 'a');
    }
    if(k <= dp.at(a-1).at(b)){
        //dp[i-1][j] == C(i-1, j)
        //現在よりaが1つ少ない == 文字列先頭がa
        //辞書順で言うと、kはbの域に達していない
        return string("a") + Str_length(a-1, b, k, dp);
    }
    else{
        return string("b") + Str_length(a, b-1, k - dp.at(a-1).at(b), dp);
    }

}

int main(){
    int A,B;
    long long K;
    cin >> A >> B >> K;

    /**
     * 文字列の順番が知りたい
     * 二次元動的計画法でいけそう
     * 最長共通部分文字列でやったときみたいに
     * aが5個,bが5個 C(5,4) + C(4,5) -> C(5,5)
     * 2つを足し合わせたのがC(5,5)までの全組み合わせ
    */
    int n_rows = 31;
    int n_cols = 31;
    int val = 0;
    vector<vector<long long>> dp(n_rows, vector<long long>(n_cols, val));

    //dp
    dp[0][0] = 1; //本来dp[0][0]は0で、dp[1][0]やdp[0][1]が1
    //dp[1][2] = dp[1][1] + dp[0][2]つまり、abが1個ずつあるところにbか。bが2個あるところにaの和
    for(int i=0; i<=A; i++){
        for(int j=0; j<=B; j++){
            if(j != 0) dp.at(i).at(j) += dp.at(i).at(j-1);
            if(i != 0) dp.at(i).at(j) += dp.at(i-1).at(j);
        }
    }

    //K番目の文字列を再帰で求める
    cout << Str_length(A,B,K,dp) << endl;
}