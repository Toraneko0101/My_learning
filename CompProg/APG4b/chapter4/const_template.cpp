#include <bits/stdc++.h>
using namespace std;

/**
 * 定数テンプレートについて
 * tupleのgetやbitset等で使われている
 * 使う場所に応じて定数を切り替えたいときに便利
*/

/**
 * 注意点
 * templateを用いて宣言された関数や構造体にtypoがあっても
 * プログラムの中で使われていない場合にコンパイルエラーにならないことがある
 * 使われていないtemplateがコンパイル時に無視されるため
 * 使用して初めてコンパイルエラーが出る
*/

/**
 * templateの実体化
 * templateは関数や構造体を自動的に生成するための設計図
 * 型専用の関数を自動的に生成する
 * templateから、実際にその関数や構造体が作られることをtemplateの実体化という
 * 実体化はコンパイラが自動的に行う
 * templateがプログラム中で一回も使われない場合実体化は行われない
 * 
*/



// modで割った余りをxに保存する
template <int MOD>
struct Modulo{
    int x;
    Modulo() {}
    Modulo(int v){
        x = v % MOD;
    }

    Modulo plus(Modulo<MOD> other){
        Modulo<MOD> result;
        result.x = (x + other.x) % MOD;
        return result;
    }
};

template <int INDEX1, int INDEX2>
void tuple_swap(tuple<int, int, int> &x){
    //交換する要素を汎用的にする
    swap(get<INDEX1>(x), get<INDEX2>(x)); 
}

int main(){
    tuple<int, int, int> x = make_tuple(1,3,4);
    //tempalte引数を指定
    tuple_swap<0, 2>(x);
    cout << get<2>(x) << endl;

    Modulo<10> a(7), b(5);
    Modulo<12> d(7), e(5);
    auto c = a.plus(b);
    auto f = d.plus(e);
    cout << c.x << endl; //(5+7)%10
    cout << f.x << endl; //(5+7)%12
}
