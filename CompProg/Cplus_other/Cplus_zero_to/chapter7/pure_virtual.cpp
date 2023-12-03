/**
 * 純粋仮想関数
 * 定義を持たない仮想関数を純粋仮想関数という
 * 純粋仮想関数にするには 仮想関数に= 0をつければいい
 * 
 * C++にはinterfaceを作るための専用の記法はない
 * メンバ関数が全て純粋仮想関数=>interfase
*/
#include <bits/stdc++.h>
using namespace std;

class Polygon{
    public:
        virtual int Area() const = 0;
};

class Rectangle : public Polygon{
    public:
        int Area() const override{
            return height_ * width_;
        }

        int height_;
        int width_;


};

int main(){
    //純粋仮想関数があるクラスのobjは作れない
    //Polygon p; //エラる
    Rectangle r;
    r.height_ = 20;
    r.width_ = 10;
    cout << r.Area() << "\n";
}