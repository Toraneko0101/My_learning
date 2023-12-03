#include <bits/stdc++.h>
using namespace std;

/**
 * コピーコンストラクタを実装した例
 * 引数にconstを使っているのはコピー元を変更するリスクを冒したくないため
 * 
 * ※コピーコンストラクタを定義していないクラスでも
 * 暗黙的なコピーコンストラクタの定義が行われないケースがある
 * 
 * 例)
 *  コピーできないデータメンバを持つ
 *  右辺値参照型のデータメンバを持つ
 *  ムーブ代入演算子やムーブコンストラクタが明示的に定義されている
*/
class Rectangle{
    public:
        //コピーするだけなら暗黙的に行われる
        //別の動作をしたければコピーコンストラクタを書く
        Rectangle(const Rectangle &r):
            height_(r.height_),
            width_(r.width_)
            {
                cout << "I called copy constructer\n";
            }

        Rectangle(int height, int width):
            height_(height),
            width_(width)
            {}
        
        int Area(){
            return height_ * width_;
        }
    private:
        int height_;
        int width_;
};

int main(){
    Rectangle r(12,21);
    Rectangle r1(r);
}