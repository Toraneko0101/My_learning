#include <bits/stdc++.h>
#define all(v) v.begin(), v.end() //allマクロ
using namespace std;

int main(){
    //charは実質的に数値なので、四則演算、比較可能
    //&& ||は短絡評価

    cout << (int)'A' << endl;
    cout << (char)65 << endl;
    char c = 'X';
    if('A' <= c && c <= 'Z') cout << "Yes" << "\n";
    cout << isdigit('a') << "\n";
    cout << isupper('n') << "\n";

    /**
     * bitsetの型として、constが使える
     * Cの配列やarrayの要素数の指定も定数である必要があるのでconstを付けた変数が利用できる
     * constついていないとダメ
    */
   const int var = 3;
   int data[var] = {0};
   cout << data[2] << "\n";

    //三項演算子をcoutの内部で利用する場合は()で囲む
    //複数行のマクロを書く場合、行末に\を書く
    //allマクロ
    vector<int> v = {2,3,1};
    sort(all(v));
    cout << v.at(0) << "\n";

    //ラムダ式
    //auto 関数名 = [](){};
    //[&]と書くことでラムダ式の外の変数を利用可能
    int max_num = 0;
    auto update_max = [&](int n){
        if(max_num < n) max_num = n;
        return max_num;
    };

    cout << update_max(5) << endl;
    cout << update_max(2) << endl;

    //再帰呼び出しのある関数をラムダ式で定義する場合
    //返り値の型と引数の型をfunction<>の中に書いたうえで[&]がいる
    //function<返り値の型(引数の型)> 関数名 = [&](引数の型 値)
    function<int(int)> sum = [&](int n){
        if(n == 0) return 0;
        int s = sum(n-1);
        return s + n;
    };
    cout << sum(3) << endl;

    //sort用のvec
    vector<int> vec = {2,3,1};
    //大きい順にsort
    //auto comp = [](int a, int b){return a > b; };
    //名前の省略
    sort(
        vec.begin(), 
        vec.end(), 
        [](int a, int b){return a > b;}
        );
    cout << vec[0] << endl;

    //next_permutationとdo-while
    sort(all(vec));
    //現在の状態を出力するためにdoがいる
    do{
        for(int x: v){
            cout << x << " ";
        }
        cout << endl;
    }while (next_permutation(v.begin(), v.end()));

    //goto
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(i==1 && j==4) goto SKIP;
            cout << format("i={}:j={}\n", i, j);
        }
    }
    SKIP:
        cout << "loop end" << "\n";


}