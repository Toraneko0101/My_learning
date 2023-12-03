/**
 * 通常はデストラクタを明示する必要はない
 * ⇒自動で行われるので
 * 
 * 必要な場合
 * ・デストラクタが呼ばれたことをログに残したい
 * ・スマートポインタ以外の資源、たとえばファイルハンドルなどの資源を解放したい場合
 * ~MyClass(){file->close();}
 * ・他のクラスやobjとの連携を、インスタンスの破棄前に切りたい場合。
*/

#include <bits/stdc++.h>
using namespace std;

class MyClass{
public:
    MyClass(){
        cout << "Constructor is called.\n";
    }

    ~MyClass(){
        cout << "Destructor is called.\n";
    }
};

int main(){
    cout << "start\n";

    {
        unique_ptr<MyClass> myobj = make_unique<MyClass>();

    }//destructor is called
    cout << "end\n";
}