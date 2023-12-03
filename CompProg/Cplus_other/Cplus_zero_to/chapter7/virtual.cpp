/**
 * 仮想関数とオーバーライド
 * 
 * 仮想関数
 *  ・派生クラスで挙動を変更できるメンバ関数
 *  ・virtual修飾子をつける(基底側で)
 *  ・派生クラスで仮想関数の挙動を変更する事⇒override
 *  ・overrideであることを明確にするため派生クラスのメンバ関数にはoverrideをつける
 *  ・overrideを行うためには仮想関数シグニチャ:引数の型やconst修飾子を厳密一致させる必要がある
 * 
 * ※overrideをつけると、関数シグニチャが厳密一致しなくなっても
 * オーバーライドに失敗しなくなる。基底クラスの仕様変更時に対応可能
 * 
 * final
 *  これ以上の継承をさせないことを明示的に宣言するキーワード
 *  または派生クラスでの仮想メンバ関数のoverrideを拒否するキーワード
 *  finalを指定した仮想メンバ関数をoverrideすると文法違反となる
 * 
 * class inherited_name final : public base_name
 * virtual auto func(int a) const -> decltype(a) final = 0;
 * 
 * 機能の必要理由
 * final
 *  baseクラスのメンバ関数をすべて把握しているとは限らない
 *  知らぬまま同名のメンバ関数を派生クラス側で使用し、オーバーライドしているかも
 *  そのためオーバーライドの禁止を明示する機能ができた
 * override
 *  overrideしたつもりで、引数の個数や型を誤っている可能性がある
 *  override指定子をつければ、オーバーライドの意思を明示でき、オーバーライドしていないときは検知できる
*/

#include <bits/stdc++.h>
using namespace std;

class Rectangle{
    public:
        virtual void  Describe() const{
            cout << "height = " << height_ << endl;
            cout << "width = " << width_ << endl;
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

        void Describe() const override{
            Rectangle::Describe();//基底の方も使う
            cout << "size = " << height_ << endl;
        }
};


int main(){
    Square s;
    s.SetSize(10);
    //overrideされているのでsquareクラスのdescribeが実行される
    s.Describe();
    //up cast
    /**
     * vvirtualもoverrideも書かないまま、アップキャストした参照を用いると、派生クラスでoverrideされたメンバ関数ではなく、
     * 基底クラスのものが実行される。
     * virtualを基底クラスのメンバ関数に付与して、派生クラスの方にoverrideを記載しておけば
     * アップキャストしても派生クラスでオーバーライドした方が使われる
     * ⇒こっちの方が普通
     * サブクラスで基底の方を用いるには オーバーライドした関数の中で、base_name::func()とすればいい
    */
    const Rectangle &r = s;
    r.Describe();
}