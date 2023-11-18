#include <bits/stdc++.h>
using namespace std;

int N,X,Y;
int A[100'009];
int grundy[100'009];

int main(){
    /*
    * 今回は山がN個あるが、何個でも取っていいわけではない
    * Grundy数
    * 一回の操作で、Grundy数がx_1,x_2,...,x_kの盤面に遷移することができる場合、
    * この盤面のGrundy数は、x_1,x_2,...,x_k以外の最小の非負整数
    * 
    * つまり、
    * 山が1つで、X=2,Y=3の場合、
    * 石の数が0個 -> Grundy : 0
    * 石の数が1個 -> Grundy : 0
    * 石の数が2個 -> Grundy : 石が0個の場面に遷移可能 -> 1
    * 石の数が3個 -> Grundy : 石が0,1個の場面に遷移可能 -> 石が0のGrundy数は0, 石が1のGrundy数は0 -> 1
    * 石の数が4個 -> Grundy : 石が1,2個の場面に遷移可能 -> (0,1) -> 2
    * 石の数が5個 -> Grundy : 石が2,3個の場面に遷移可能 -> (1,1) -> 0
    * 石の数が6個 -> Grundy : 石が3,4個の場面に遷移可能 -> (1,2) -> 0
    * 石の数が7個 -> Grundy : 石が4,5個の場面に遷移可能 -> (2,0) -> 1
    * 石の数が8個 -> Grundy : 石が5,6個の場面に遷移可能 -> (0,0) -> 1
    * 
    * Grundy数が0の時、負けの状態
    *   Grundy数が0の盤面に遷移できないとき、Grundy数は0
    * Grundy数が1以上の時、勝ちの状態
    *   Grundy数が0の盤面に遷移できるとき、Grundy数は1以上
    * 
    * 山が2つ以上の場合
    *   山iのGrundy数をG_iとすると、
    *   G_1 XOR G_2 XOR ... XOR G_N = 0の時、後手必勝
    *   G_1 XOR G_2 XOR ... XOR G_N ≠ 0の時、先手必勝
    * 
    * つまり、Grundy数を求めてから、XORを取ればいい
    */

    cin >> N >> X >> Y;
    for(int i=1; i<=N; i++) cin >> A[i];

    //grundy
    for(int i=0; i<=100'000; i++){
        //X,Yを引いたときのGrundy数(0~2)のうち、どれが出現するか
        bool Conditions[3] = {false, false, false};
        if(i >= X) Conditions[grundy[i-X]] = true;
        if(i >= Y) Conditions[grundy[i-Y]] = true;

        if(Conditions[0] == false) grundy[i] = 0;
        else if(Conditions[1] == false) grundy[i] = 1;
        else grundy[i] = 2;
    }

    //xor
    int XOR_sum = 0;
    for(int i=1; i<=N; i++) XOR_sum = (XOR_sum ^ grundy[A[i]]);
    if(XOR_sum) cout << "First" << endl;
    else cout << "Second" << endl;
    return 0;
}