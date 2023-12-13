#include <bits/stdc++.h>
using namespace std;

/**
 * assert
 * 実行時に条件を満たさないと
 * std::abortを呼び出し、異常終了する
 * 
 * ⇒開発中のバグ検知用の機能
 * ⇒NDEBUGが定義されるリリース用のビルドでは無効となる
 * ⇒ -DNDEBUGを渡すと、NDEBUGが定義できる
*/

int Max_rtn(const vector<int> &v){
    assert(!v.empty()); //空要素ならabort

    //int型で表現できる最小値
    int max = numeric_limits<int>::min();
    for(auto e : v){
        if (e > max) max = e;
    }
    return max;
}

int main(){
    vector<int> v1 = {5,6,2,3,1};
    vector<int> v2;

    cout << Max_rtn(v1) << "\n";
    cout << Max_rtn(v2) << "\n";
    return 0;

//g++ -std=c++20 assert.cpp
// 6
// a.out: assert.cpp:15: int Max_rtn(const std::vector<int>&): Assertion `!v.empty()' failed.
// 中止

//g++ -std=c++20 -DNDEBUG assert.cpp
// 6
// -2147483648
}


