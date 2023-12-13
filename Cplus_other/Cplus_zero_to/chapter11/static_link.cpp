/**
 * 静的ライブラリ
 * 複数のオブジェクトファイルを1つのファイルにまとめ、
 * [リンク時]にオブジェクトファイルの代わりとして使用する
 * ⇒そのファイルをリンクする事＝静的リンク
 * 
 * $ ar rc libhoge.a add.o sub.o
 * ⇒add.cppとsub.cppをコンパイルして生成される二つのobjファイル
 * add.o, sub.oから静的ライブラリ、libhoge.aを生成する
 * 
 * ar -> アーカイブを操作
 * rc -> アーカイブを作成してファイルを追加
 * 
 * $ ar t libhoge.a
 * ⇒ アーカイブの内容を閲覧
 * 
 * $ g++ -std=c++20 static_link.o libhoge.a
 * ⇒libhoge.aを静的リンク
*/
#include <iostream>
//関数宣言があれば、定義がなくてもコンパイルはする
int Add(int a, int b);
int Sub(int a, int b);

int main(){
    std::cout << Add(1,2) << "\n";
    std::cout << Sub(3,4) << "\n";
    return 0;
}