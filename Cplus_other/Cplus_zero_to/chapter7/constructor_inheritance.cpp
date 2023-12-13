/**
 * 派生クラスのコンストラクタは
 * 暗黙的に基底クラスのデフォルトコンストラクタを呼び出す
*/

#include <bits/stdc++.h>
using namespace std;

class Rectangle{
public:
    Rectangle(): height_(0), width_(0){
        cout << "Rectangle::Rectangle() is called\n";
    }

    Rectangle(int height, int width) :
        height_(height), width_(width){}

    int Area() const{
        return height_ * width_;
    }
private:
    const int height_;
    const int width_;
};

class Square : public Rectangle{
public:
    Square(){
        cout << "Square::Square() is called\n";
    }
    //基底のコンストラクタを明示的に呼び出す
    //派生クラスの初期化リストとして呼び出す場合は、
    //基底クラス::コンストラクタはコンストラクタとして省略可能
    Square(int size) : 
        //Rectangleのコンストラクタの定義が実行される
        Rectangle(size, size),
        another_member(size * 2)
    {}
    int another_member;
};

int main(){
    //baseのコンストラクタも呼ばれていることが分かる
    //基底⇒派生の順番で呼ばれる
    Square s; 
    cout << "area = " << s.Area() << "\n";

    Square s1(10);
    cout << "area = " << s1.Area() << "\n";

}