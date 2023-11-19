#include <bits/stdc++.h>
using namespace std;
#define rep(i, s, n) for( int i=(s); i < (int)(n); i++) //repマクロ

int incre(int x){
    // return ++x; //4
    return x++; // 3
}
int main(){
    //負の数の剰余, Bの正負にかかわらず、Aの正負と一致する
    cout << 7 % -5 << endl;     //2
    cout << 7 % 5 << endl;      //2
    cout << -7 % -5 << endl;    //-2
    cout << -7 % 5 << endl;     //-2
    // x++ 評価してから1増やす ++x 1増やしてから評価する
    cout << incre(3) << endl;
    //repマクロ
    rep(i,0,3){
        if(i==0) continue;
        if(i==2) break;
        cout << i << ":Neko" << endl;
    }

}