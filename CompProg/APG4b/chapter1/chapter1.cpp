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

    //文字列
    string str1 = "Neko!!!\nNyanko";
    for(int i=0; i<str1.size(); i++){
        cout << str1.at(i);
    }
    cout << endl;
    cout << str1.front() << endl; //str1.back()
    str1.clear();
    if(str1.empty()) cout << "a" << endl;
    //getline(cin, s) //変数sで行単位で入力を受け取る

    //配列: 全要素が一致していた時、==で比較可能
    vector<int> vec(3, 10);
    vec = vector<int>(2, 11); //配列変数の上書き
    vec.push_back(12);
    vec.erase(vec.begin()); //最初の要素を削除
    vec.insert(vec.begin()+1, 100);
    
    for(int i=0; i< vec.size(); i++) cout << vec.at(i) << endl;
    cout << typeid(vec.size()).name() << endl; //m:unsigned long

    //stl
    //min, max, swap, reversem sort
    cout << max({1,2,4s}) << endl;
    vector<int> v = {1,5,3};
    reverse(v.begin(), v.end());
    cout << v.at(0) << endl;
    sort(v.begin(), v.end(), greater<int>());
    cout << v.at(0) << endl;
    /**
     * 引数の実行順序
     * gcc : 最後の引数の式から実行
     * clang: 最初の引数の式から実行
    */

   //templateに関しては後程
   

}