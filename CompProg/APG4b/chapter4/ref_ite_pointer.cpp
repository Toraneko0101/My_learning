#include <bits/stdc++.h>
using namespace std;
/**
 * 参照・イテレータとの関係
 * 参照やイテレータはポインタをより扱いやすく
 * するために用意された機能
*/

//参照 と pointer
void f(int &ref){
    ref = 2;
}

void g(int *ptr){
    *ptr = 2;
}

int main(){
    int x = 1;
    f(x); //参照渡し:渡す側で&を付けるだけだから楽。
    cout << x << endl;

    int y = 1;
    g(&y); //yのアドレスを渡す必要がある
    cout << y << endl;

    //pointer vs iterator: end()等がある分、簡単に書ける
    vector<int> a = {1,2,3};
    for(auto it = a.begin(); it != a.end(); it++){
        cout << *it << endl;
    }

    vector<int> b = {1,2,3};
    int *begin_addr = b.data(); //bのデータの先頭アドレスを返す == &b[0]
    for(int *ptr = begin_addr; ptr < begin_addr + 3; ptr++){
        cout << *ptr << endl;
    }

    //範囲for
    vector<int> c = {1,2,3};
    for(int buf: c) cout << buf << endl;

    /**
     * voidポインタ
     * 任意のポインタ値を扱える
     * 指す先へのアクセスはできない
     * アクセスする場合は元のポイント型にキャストする
    */

   int x1 = 123;
   string y1 = "hello";
   double z1 = 3.5;

   vector<void *> ptrs = {&x1, &y1, &z1};
   //キャストしてから使う
   int *xp = (int *)ptrs[0];
   string *yp = (string *)ptrs[1];
   double *zp = (double *)ptrs[2];
   cout << *xp << endl;
   cout << *yp << endl;
   cout << *zp << endl;

   /**
    * ポインタの使いどころ
    * 木構造やグラフのデータ構造を表現する際
    * メモリを効率的に使いたい時=ヒープ
   */

}