#include <bits/stdc++.h>
using namespace std;

int main(){
    set<int> x = {12,7,24,67};
    cout << *(x.begin()) << endl; //最小値が保持されるので7
    //countはcount(first, end, element);findもそう
    //0以上の2の倍数をcountする
    //コンテナ全体を一度に操作するので大きすぎると効率的でない可能性がある
    auto n = count_if(x.begin(), x.end(), [](const int v){
        if(v <= 0){
            return false;
        }
        if(v % 2 == 0){
            return false;
        }
        return true;
    });

    cout << n << "\n";

    //元のコンテナを直接変更しないので、大きなコンテナに対しても効率的に動作する
    //範囲forで0以上の2の倍数をcount
    int cnt = 0;
    for(auto i: views::filter(x, [](int a){
        if(a < 0 || a % 2 != 0) return false;
        return true;
    })){
        cnt++;
        cout << i << "\n";
    }cout << cnt << "\n"; //2

    /**
     * 範囲forの節で見たムーブセマンティクスは後程やる
    */
}