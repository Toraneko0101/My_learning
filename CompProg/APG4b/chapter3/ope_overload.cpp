#include <bits/stdc++.h>
using namespace std;

struct MyPair{
    int x;
    string y;
    MyPair(){}
    MyPair(int _x, string _y) : x(_x), y(_y){}
    //なるほど引数には同じ型のobjを取るってことか
    //デフォルトだと構造体同士の足し算はできない
    MyPair operator+(const MyPair &other){
        //戻り値がMyPairなので別のobjを宣言し、そいつをreturnする
        MyPair ret;
        ret.x = x + other.x;
        ret.y = y + other.y;
        return ret;
    }

    void operator-(const MyPair &other){
        x -= other.x;
    }
    //定義しない場合、全てのメンバ変数がそのまま代入される
    void operator=(const MyPair &other){
        cout << "= operator called" << "\n";
        x = other.x;
        y = other.y;
    }

    /**
     * *,/,%,<,>,等のほか、&&,||も可能
     * たぶん=>や->などもいける
    */
};

//構造体の外側で演算子オーバーロードを使う
//自分に対して比較できないので、引数は2つ必要
//関数みたい
pair<int, int> operator+(pair<int, int> a, pair<int, int> b){
    pair<int, int> ret;
    ret.first = a.first + b.first;
    ret.second = a.second + b.second;
    return ret;
}

//pairに対して比較方法を変更(2番目優先)
bool operator>(pair<int,int> a1, pair<int,int> a2){
    if(a1.second == a2.second) return a1.first > a2.first;
    return a1.second > a2.second;
}

//比較関数(trueならそのまま。falseなら入れかえ:先頭小さく)
bool compare(pair<int,int> a1, pair<int,int> a2){
    if(a1.second == a2.second) return a1.first < a2.first;
    return a1.second < a2.second;
}

int main(){
    MyPair a = {123, "hello"};
    MyPair b = {456, "world"};
    MyPair c = a + b;
    a - b;
    cout << a.x << endl; //-333
    cout << format("c.x = {}\n", c.x);
    cout << format("c.y = {}\n", c.y);

    MyPair d;
    d = a;

    pair<int, int> p1 = {1,2};
    pair<int, int> p2 = {3,4};
    pair<int, int> p3 = p1 + p2;
    cout << p3.first << " , " << p3.second << "\n";
    pair<int, int> p4 = {11,1};

    vector<pair<int,int>> vec;
    vec.push_back(p1);
    vec.push_back(p2);
    vec.push_back(p3);
    vec.push_back(p4);
    //比較関数を定義
    sort(vec.begin(), vec.end(), compare);
    for(auto v : vec){
        cout << format("{}:{}\n", v.first, v.second);
    }

    //STLのコンテナの要素として使う場合の注意
    /**
     * mapのKeyとして構造体を使う場合
     * priority_queueの要素の型として構造体を使う場合
     * 構造体の配列に対してsortを使う場合
     * ⇒比較演算子<のオーバーロードが必要
    */

   /**
    * メンバ初期化子リスト
    * メンバ変数が参照型の場合、constructor内で初期化できない
    * MyPair() : x(123), y("Hello"){}とする
    * コンストラクタに書くのは初期化ではなく代入
    * メンバは各クラスのデフォルトコンストラクタで初期化している
    * そのため初期化+代入という二度手間が発生している
    * 初期化子リストを使うことで、初期化だけで済む
    * constは初期化しかできないからコンストラクタ内では代入できない
    * ⇒初期化子リストを使えばいい
   */
  MyPair e(3, "Neko");
  cout << e.x << endl;

}