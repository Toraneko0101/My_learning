/**
 * データメンバ = メンバ変数
 * データメンバの参照は.
 * データ関数は外にもかける
*/
#include <bits/stdc++.h>
using namespace std;

class Rectangle{
    public:
        /**
         * クラス宣言の中でメンバ関数を定義すると
         * 暗黙的にinline指定される
         * そのためhppのクラス宣言でメンバ関数を定義しても
         * リンク時エラーにならない
         * hppでクラス宣言とは別にメンバ関数の定義を行うと
         * リンク時にエラーとなる。直前にinlineをつければいける
         * ⇒理由
         * ⇒ヘッダファイルを複数のソースからincludeするときのことを考える
         * ⇒すると関数定義が書くソースファイルにコピーされるが、
         * ⇒これは同名の関数の定義が複数存在する状態を引き起こす
         * ⇒★inline修飾子を付けることで、関数の多重定義が許容される
         * ⇒クラス宣言の中のメンバ関数は暗黙的にinline修飾子がついているので、複数からincludeしても問題ない
         * ⇒ソースファイルに直接書いた場合、複数ファイルに登場する可能性はないので問題ない
         * ⇒ソースファイル内で同名の関数が定義されている場合、その関数定義もヘッダファイルに移動し、inlineキーワードを付ける
         * 
        */

        /**
         * ところで、そもそもinline展開とは？
         * 関数の内容をそのまま展開する事
         * ⇒プログラムの高速化のため
         * ⇒呼び出しの際に生じるメモリ移動の処理をなくすため
         * ⇒現在ではコンパイラが行ったりする
         * 
         * inline関数
         * ⇒関数定義の前にinline修飾子をつけると
         * 通例、inline展開される
         * inlineメンバ関数はクラスを定義したヘッダに書かないと、どこに展開していいのかコンパイラが判断できなくなる
         * 
        */

        /**
         * constメンバ関数
         * 引数リストの後にconstをつけることで、constメンバ関数になる
         * データメンバの変更が許容されない
        */

       /**
        * thisポインタ
        * メンバ関数ではthisで自オブジェクトのポインタを取得可能(ポインタ経由)
       */
        int Area() const{
            return this->height_ * this->width_;
        }
        pair<int,int> Print();
        int height_;
        int width_;
};

//クラス宣言とは別に定義
pair<int,int> Rectangle::Print(){
    return {height_ , width_};
}


int main(){
    Rectangle r;
    r.height_ = 10;
    r.width_ = 20;

    //クラスのオブジェクトをポインタで扱う場合
    Rectangle rectangle;
    Rectangle* r1 = &rectangle;
    (*r1).height_ = 0; //括弧を外すとエラる。優先順位が、. > *なので、r1は生ポインタなので当然、height_というデータメンバを持っていない。
    r1->height_ = 10;
    r1->width_ = 20;
    cout << rectangle.height_ << "\n";

    //参照する場合
    Rectangle &r2 = rectangle;
    r2.width_ = 40;
    cout << rectangle.width_ << "\n";

    auto [h, w] = r2.Print();
    cout << h << ":" << w << "\n";
}