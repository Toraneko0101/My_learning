#include "a.hpp"
#include <bits/stdc++.h>
using namespace std;
/**
 * a.hppでa.cppのプロトタイプ宣言
 * main.cppでincludeして取り込む
*/

extern int x;

int main(){
    DoSomething();
    DoSomething1();
    DoSomething2();
    DoSomething3();
    DoSomething4();
    DoSomething5();
    cout << x << endl;
    return 0;
}