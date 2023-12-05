/**
 * 通常はデストラクタを明示する必要はない
 * ⇒自動で行われるので
 * 
 * 必要な場合
 * ・デストラクタが呼ばれたことをログに残したい
 * ・スマートポインタ以外の資源、たとえばファイルハンドルなどの資源を解放したい場合
 * ~MyClass(){file->close();}
 * ・他のクラスやobjとの連携を、インスタンスの破棄前に切りたい場合。
 * 
 * その他
 * ・RAII技法が使われたリソース管理クラスをデータメンバに持つ場合
 * それらのデストラクタは自動的に呼び出される
 * ・デストラクタから例外を投げてはいけない。暗黙の裡にnoexcept指定されるので
 * 
 * RAII
 * ・クラス変数の寿命が尽きたときにデストラクタが呼ばれるという性質を利用し、
 * リソースの割り当てと解放を紐づけて管理したもの
 * 
 * 継承
 * ・派生クラスのデストラクタは基底のデストラクタを暗黙呼び出しする
 * ・派生⇒基底の順でデストラクタは呼び出される
 * ・アップキャストした場合、派生のデストラクタは呼び出されない
 * ・そのため基底のデストラクタを仮想関数にして、派生ではデストラクタをオーバーロードする
 * ※STLコンテナはポリモーフィズムをサポートしていないので(virtualがない)、基底の参照を使って
 * 派生のobjにアクセスすると、派生のデストラクタが呼ばれなくなる
 * ⇒protected継承やprivate継承を行えば、アップキャストは直接的に不可能になる?
 * ⇒そもそもSTLコンテナを継承して使うのがよくないのかも
 * ⇒STLコンテナをメンバとして持つようなクラスを生成するべきかも
 * 
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