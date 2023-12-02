#include <bits/stdc++.h>
using namespace std;

//プロトタイプ宣言は重複してもいい
void Test();
void Test();

/**
 * 変数の宣言。変数xがint型であることを宣言し、記憶域は割り当てない
 * また値の変更はできない
 * externは変数が他のソースファイルで定義されていることを示す
 * extern int x;
 * 変数の定義。変数xがint型であり、値を保存するための記憶域がプログラムで割り当てられる
 * int x;
 * 
 * 例)
 * test1.cppでint x = 1;と定義
 * test2.cppでextern int x;とする
 * すると、test2.cppからxの値にアクセス可能
 * しかし、test2.cppで x = 3;とするのは不可
 * またexternを使用したにもかかわらず他のファイルで変数が定義されていない場合、リンク時エラーが発生する
 * 定義の重複は許されない。定義がないとエラる。
*/

void Test(){
    cout << "test" << "\n";
}