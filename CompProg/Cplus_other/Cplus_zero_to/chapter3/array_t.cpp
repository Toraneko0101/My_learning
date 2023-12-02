#include <bits/stdc++.h>
using namespace std;

void func(array<int, 5> x){
   for(int i=0; i<(int)size(x); i++){
        cout << x[i] << " ";
   }cout << "\n";
}

int main(){
    /**
     * 初期化時に2重括弧ガイル
     * 要素数を一緒にもてるので持ち運び便利
    */
    array<int, 5> x = {{0,1,2,3,4}};
    cout << size(x) << endl;
    //配列のコピー
    array<int, 5> y{};
    y = x;
    //関数
    func(y);
}