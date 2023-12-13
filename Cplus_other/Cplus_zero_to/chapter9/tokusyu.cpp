#include <bits/stdc++.h>
using namespace std;

/**
 * 特殊化
 * ⇒templateで実引数に応じて関数やクラスを生成する事
 * ⇒暗黙的インスタンス化ともいう
 * ⇒特殊化はコンパイラが行うのでhppでtemplateを使う場合は、
 * ヘッダで定義を行う(ヘッダで実装するので複数include対策でinline指定がいる)
 * ⇒しかしこれはコンパイル速度の低下につながる
 * 
 * <対策1>
 * ヘッダファイルで宣言を行い、ソースで生成する場合
 * 明示的なインスタンス化が必要になる
 * 例)
 * 
 * <hpp>
 * template <typename T>
 * T Sum(T a, T b);
 * 
 * <cpp>
 * template <typename T>
 * T Sum(T a, T b){return a + b;}
 * 
 * //明示的なインスタンス化
 * tempalte int Sum<int>(int, int)
 * <問題>
 * 明示的なインスタンス化を行った型しか使用可能でなくなる
 * 明示的なインスタンス化を増やして共有ライブラリにするとそのサイズがでかくなる
 * 
 * <対策2>
 * extern templateを使うらしい
*/

/**
 * 完全特殊化
 * すべてのparamが確定したときに別の定義を書ける
 * ⇒特定のtemplate引数に関する挙動の変更
*/

template <typename T>
T DoSomething(T a, T b){return a + b;}

//完全特殊化を行うことを指定する
//クラスに対する完全特殊化も同一
template <>
double DoSomething<double>(double a, double b){return a * b;}

int main(){
    cout << DoSomething(2,3) << "\n"; //5
    cout << DoSomething(2.0,3.0) << "\n"; //6
}

//classTemplateの一部のtemplate引数を確定させたり、制限することができる
//⇒部分特殊化