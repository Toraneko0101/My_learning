/**
 * constructor
 * objを作成する際に呼び出されるメンバ関数
 * データメンバの初期化などに使われる
*/
#include <bits/stdc++.h>
using namespace std;

class Rectangle{
    public:
        /**
         * デフォルトコンストラクタ
         * 値を1つも受け取らないコンストラクタ
        */
        Rectangle() : height_(0) , width_(0) {}
        /**
         * データメンバの初期化
         * {}の中に書かない限り、代入ではなく初期化
         * なので、constメンバの値も設定可能
         * 
         * リスト初期化
         * {}を利用した初期化子のリストによるobjや参照の初期化
         * User u = {1,2,3}みたいなやつ
         * 
         * 初期化子リスト
         * height_(height)みたいなやつ
         * コンストラクタ名の後にコロンを置き、変数名(初期値)で記述
         * 複数あればカンマでつなぐ
         * 
        */
        Rectangle(int height, int width) :
            height_(height), width_(width){}
        //クラス宣言と別に、コンストラクタを定義することもできる
        Rectangle(int size);
        
        int Area() const{
            return height_ * width_;
        }

    private:
        const int height_;
        const int width_;
};

Rectangle::Rectangle(int size) : height_(size), width_(size){}

int main(){
    Rectangle r{13,21};
    cout << r.Area() << "\n";

    //デフォルトコンストラクタを使ってobjを作成する場合
    //()や{}は不要
    Rectangle r1;
    cout << r1.Area() << "\n";
    
}
