/**
 * 0,1:使う意味ない
 * 2: pair
 * 3以上: 構造体でも可
 * 
 * tupleの型や組み合わせはコンパイル時に決定しておく必要あり
 * 型推論すると、using namespace std::literals::string_literalsでs指定しない限り
 * 文字列リテラルがconst char*型になるので注意
 * 
 * 
*/

#include <bits/stdc++.h>
using namespace std;

struct Human{
    int age;
    double height;
};

struct Data{
    double x,y,z;
    string str;
};
int main(){
    std::tuple<int,double, std::string> t{100, 1.1 , "aa"};
    //<>の中身は、定数templateなので、コンパイル時定数である必要あり
    cout << std::get<0>(t) << "\n";
    //std::tupleが同じ型の要素を1つしか持たない場合
    cout << std::get<int>(t) << "\n";

    /**
     * 構造体 vs tuple
     * struct:
     *  ・見通しがよくなる
     *  ・std::tupleはtrivially copyableになることが保証されていない
     * tuple:
     *  ・比較演算の自動定義 -> 宇宙演算子の登場で優位性があまりなくなった
     *  ・コードの行数が少なくて済む
     *  ・型の名前を考える必要がない
     * 
     * trivially copyable
     *  オブジェクトがメモリコピーによって単純かつ安全にコピー可能
     *  structならメンバが上記なら、通常はこれを満たす
     *  そのため、単純なデータ構造を表現する場合には便利
     *  std::memcpy()可能な型であるとも言い換えられる
    */

    //memcpy(これなんか利点ある?)
    Human h1;
    Human h2;
    h1.age = 12;
    h1.height = 1.65;
    std::memcpy(&h2, &h1, sizeof(Human));
    cout << h2.age << endl;
    cout << h2.height << endl;

    Data d{1.1, 2.2, 3.3, "neko"};
    cout << d.x << d.y << d.z << d.str << "\n";

    /**
     * tupleの基本
     * ・初期値を与えない各値は初期化
     * ・cinで入力したい場合は、std::get<0>(t)等に対していれる
     * ・別のtupleからは=で代入
     * ・要素の個数が同じで、各要素について=を用いた代入が可能なら型が異なっていても可能
     * ・複数の値を返す巻数を作るときにstd::tupleを使って、構造化束縛で戻すのがいい
     * ⇒構造体束縛で何が行われているかは後ほど
    */
    auto func = []() ->std::tuple<int, double, string> {
        return{100, 1.1, "aa"};
    };

    auto [a,b,c] = func();
    //std::tie()の使いどころさん
    //・既にある変数を使って構造化束縛を行うことはできない
    //・一部の要素に対してのみ構造化束縛を行うことはできない
    //std::tieは各要素が参照のtupleを作る。そのため要素をそれぞれの変数に代入可能
    std::tie(a,b,c) = make_tuple<int, double, string>(2,1.4,"neko");
    //ignoreで無視も可能
    std::tie(a, std::ignore, c) = make_tuple<int, double, string>(8,1.9, "inu");
    cout << a << " " << b << " " << c << "\n";

    //大きさ比較 -> ラムダで変えればいい

    //追加するときはemplace_back
    vector<tuple<string, int, int>> v;
    v.push_back({"aaa", 100, 200});
    v.emplace_back("aaa", 100, 200);

    //tupleの要素を引数に当てはめて関数を呼び出す
    //std::apply(f,t) t(tuple)の要素をそれぞれの引数に当てはめて関数f()を呼び出す
    auto func1 = [](int a, double b, const std::string &c){
        cout << a << " " << b << " " << c << "\n";
    };

    auto func2 = [](int a, double b){
        cout << a << ", " << b << "\n";
    };

    tuple<int,double, string> t1{100,1.1, "ac"};
    //invoke(関数呼び出し演算子をサポートしている任意の型に使うやつ)のtuple版みたいなもんか?
    //invoke(func, args) -> func(args...)
    //apply(func, make_tuple(args...)) -> func(args...)
    std::apply(func1, t1);
    std::invoke(func2, 10, 1.2);

}
