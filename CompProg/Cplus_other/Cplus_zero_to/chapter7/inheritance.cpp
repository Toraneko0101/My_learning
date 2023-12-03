#include <bits/stdc++.h>
using namespace std;

/**
 * メンバを参照できる範囲はアクセス指定子で制限する
 * デフォルト(無表記)はprivate(structのデフォルトはpublic)
 * メンバに対するアクセス指定子
 * public:, private:という風に指定する
 * protectedなら継承したクラス内でも参照可能
 * アクセス指定子は、次のアクセス指定子が出現するまでが有効範囲
 * アクセス指定子は何度でも使用可能（コーディング規約で指定されることもある）
*/
class Rectangle{
    public:
        int Area() const{
            return height_ * width_;
        }

        int height_;
        int width_;
};

/**
 * 継承に対するアクセス指定子
 * アクセス指定子によって、基底クラスのメンバを参照できる範囲をさらに制限可能
 * class Sub1 : public Base{}; //public継承
 * class Sub4 : Base{}; //defaultはprivate継承
 * 
 * public継承 ⇒基底クラスのpublicメンバには派生でpublicが指定可能
 * protectedメンバにはprotectedメンバとして指定可能
 * 
 * protected継承⇒基底クラスのpublicやprotectedは派生のprotectedとして指定可能
 * 
 * private継承⇒基底のpublicやprotectedは派生でprivateとして指定可能
 * 
 * interfaseのクラスを継承して実装する場合はpublicで
 * 
 * つまり、下のpublic Rectangleを、privateにした場合、
 * Square s;
 * s.height_ = 10;みたいなアクセスは不可になる
 * Rectangle r;
 * r.height = 10;は可能だが
*/
class Square : public Rectangle{
    public:
        void SetSize(int size){
            height_ = size;
            width_ = size;
        }
};


int main(){
    Square s;
    s.SetSize(10);
    cout << s.Area() << "\n";
    cout << s.height_ << "\n";

}
