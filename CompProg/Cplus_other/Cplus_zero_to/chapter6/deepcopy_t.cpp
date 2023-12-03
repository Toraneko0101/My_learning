/**
 * C++のcopyは基本的にはdeep
 * 実体分コピーするので、コピー分のメモリが必要
 * 編集してもコピー元には影響なし
 * 
 * shallow
 *  ・ポインタをコピー or 参照
 *  ・ポインタの向き先だけがコピーされる
*/
#include <bits/stdc++.h>
using namespace std;
void ChangeToFifty(int &a){
    a = 150;
}
int main(){
    int a = 100;
    ChangeToFifty(a);
    cout << a << endl;
}