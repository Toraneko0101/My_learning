#include <bits/stdc++.h>
using namespace std;

#include "other.hpp"

namespace{
    int hoge = 0; //グローバルスコープの定義重複
}
int main(){
    Print();
    int hoge = 10;
    cout << ::hoge << endl;
    cout << hoge << endl;
    //cout << x << endl; //error
}