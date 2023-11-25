#include <bits/stdc++.h>
using namespace std;
/**
 * 関数テンプレートの例
 * template <typename T> == template <class T>
*/

//a < bなら　aをbで更新
//更新されたらtrueを返す

template <typename T>
bool chmax(T &a, const T &b){
    if (a < b){
        a = b;
        return true;
    }
    return false;
}

template <typename T>
bool chmin(T &a, const T &b){
    if (a > b){
        a = b;
        return true;
    }
    return false;
}

int f(int n){
    //適当な関数
    return n*n - 8*n + 3;
}

int main(){
    //f(1),...,f(10)の最小値と最大値を求める
    int ans_min = 1e9;
    int ans_max = -1e9;
    for(int i=1; i<11; i++){
        chmin(ans_min, f(i));
        chmax(ans_max, f(i));
    }
    cout << ans_min << " " << ans_max << "\n";
    return 0;
}