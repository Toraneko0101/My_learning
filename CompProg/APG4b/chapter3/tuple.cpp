#include <bits/stdc++.h>
using namespace std;

int main(){
    tuple<int, string, bool> data(1, "Hello", true);
    //idxは0から。<>の中の値は変数にできない
    get<2>(data) = false;
    get<1>(data) = "Nyanko!!!";
    cout << get<1>(data) << endl;
    //make_tupleで作ることも可能
    data = make_tuple(2, "INUUU", true);
    //分解
    int a;
    string s;
    bool f;
    tie(a,s,f) = data;
    cout << format("{} {} {}\n", a, s, f);

    //比較(sortする際もデフォルトは先頭から基準)
    //型エイリアスで型名が長くなることを防ぐ(typedefはtemplateをサポートしていない)
    using ti3 = tuple<int,int,int>;
    ti3 data1(1,2,3);
    ti3 data2(2,-9,-5);
    if(data1 > data2) cout << "data1 > data2" << endl;
    else cout << "data1 <= data2" << endl;
    //ignoreでtieで受け取るとき値を捨てる
    int a1;
    tie(ignore, ignore, a1) = data1;
    cout << a1 << endl;

    //型エイリアスで2次元vecを書く
    using vi = vector<int>;
    using vvi = vector<vi>;
    int N = 10, M = 20;
    vvi d(N, vi(M,1)); //N*Mの2次元配列;
    cout << d.at(9).at(4) << "\n";
}