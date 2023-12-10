/**
 * プリプロセッサ
 * ⇒コンパイルを行う前にソースファイルの変換などを行うプログラム
 * 
 * インクルード
 * #includeは指定ファイルを読み込み展開する
 * 単純なファイル展開なのでインクルードガードが必要になる
 * ""はカレントから検索
 * <>は標準のインクルードディレクトリから検索
 * 
 * マクロ
 * 有効化するには#define
 * 無効化するには#undef
 * ⇒固定文字列の場合は、defineではなくconstexprを使う
 * ⇒関数の場合、引数を使用して変換する
 * #define rep(i,n) for(int i=0; i < (int)n; i++)
 * 意図しない挙動にならないように、括弧で囲む必要などもある
 * 改行するときは\を用いる
 * 
 * __cplusplusは実用的
 * ⇒これはC++のversionを表す数値を取得するもの
 * C++11なら201103Lという値に置換される
 * 
 * 条件
 * #if, #elif #else #endifでコードの有効無効を分別できる
 * definedでマクロが定義されているかどうかを条件にもできる
 * 
 * #ifdefと#ifndef
 * これは#if definedと #if !definedの略
 * つまり、
 * #ifndef SAMPLE_H_というのは
 * #if !defined SAMPLE_H_
 * もしSAMPLE_H_が定義されていなければ以下を実行するという意味。
 * ⇒これを使ってインクルードガードは実現されている
 * ⇒※通常は#pragma onceだが
 * ⇒特定の条件が満たされたときにヘッダファイルの内容をスキップなどしたい場合は、#ifndefを使ってみてもいいかもしれない
*/

#include <bits/stdc++.h>
using namespace std;

int main(){
    //定義済みマクロ名
    cout << __FILE__ << endl; //ファイル名
    cout << __LINE__ << endl; //現在の行番号
    cout << __DATE__ << endl; //日付
    cout << __TIME__ << endl; //コンパイル時の時刻
    cout << __cplusplus << endl; //202002: versionによって分離も可能
    cout << __func__ << endl; //関数名
    cout << __STDCPP_THREADS__ << "\n"; //プログラムが複数のスレッドを実行できる場合1

    #if false
        cout << "true" << "\n";
    #elif 1==1
        cout << "adnormality" << "\n";
    #else
        cout << "abrerrant" << "\n";
    #endif
}