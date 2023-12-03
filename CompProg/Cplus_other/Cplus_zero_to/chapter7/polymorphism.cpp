#include <bits/stdc++.h>
using namespace std;

/**
 * from 派生クラスからの参照やポインタ
 * to 基底クラスの参照やポインタ
 * 上記のような型変換をアップキャストという
 * ⇒派生クラスのobjを、基底クラスの参照やポインタで扱える
*/

class Rectangle{
    public:
        int Area() const{
            return height_ * width_;
        }
        int height_;
        int width_;
};

class Square : public Rectangle{
    public:
        void SetSize(int size){
            height_ = size;
            width_ = size;
        }
};

int main(){
    Rectangle rectangle;
    rectangle.height_ = 12;
    rectangle.width_ = 15;
    Square s;
    s.SetSize(10);
    //アップキャストは暗黙的に行われる
    const Rectangle &r = s;
    //同じ型のvecに入れてまとめて扱えるので便利
    vector<Rectangle> shape;
    shape.emplace_back(r);
    shape.emplace_back(rectangle);
    for(auto s: shape){
        cout << "area = " << s.Area() << endl;
    }

    /**
     * ダウンキャストについて
     * 基底⇒派生への型変換
     * dynamic_cast
     *  仮想関数を持ったクラスに限定される
     *  実行時にキャストの成否を判断し、継承関係が不正なら失敗する
     *  ポインタならnullptr,参照ならstd::bas_castが失敗時には返る
     * 
     * static_cast
     *  実行時の型の情報をcheckしない
     * 
     * そのためできることならdynamic_castを利用する
     * もっというと、ダウンキャストを書かなくてもいいようなプログラムにするのが望ましい
    */
}