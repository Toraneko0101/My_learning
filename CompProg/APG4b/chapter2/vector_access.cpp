#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> v1 = {10,20,30,40};
    //違いはout_of_rangeのエラーがちゃんと出るか
    //後者の方が例外チェックのために内部でifを使うので遅い
    cout << v1[0] << "\n";
    v1.at(0) = -1;
    cout << v1.at(0) << "\n";

    //空の配列で使うと範囲外アクセスになる
    cout << v1.front() << "\n";
    cout << v1.back() << "\n";
    return 0;
}