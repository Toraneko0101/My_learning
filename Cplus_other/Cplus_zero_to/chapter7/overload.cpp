#include <bits/stdc++.h>
using namespace std;

class Integer{
public:
    explicit Integer(int value) : value_(value){}

    int Value() const{
        return value_;
    }

    //非メンバの場合左辺が第一引数、右辺が第二引数となる
    //メンバの場合、左辺のメンバに対して、右辺が引数
    Integer operator+(const Integer& other) const {
        Integer tmp(this->Value() + other.Value());
        return tmp;
    }

    //オーバーロードすると、後置がobjのcopyをすることがよくわかる
    //前置はobjを直接インクリメントするので引数を持たない
    //後置はobjのcopyを行い、そのあとでobj自体をインクリメントするので、元の値が引数として返る
    Integer& operator++(){
        //前置
        ++value_;
        return *this; //自身を返す;
    }

    Integer operator++(int){
        //そのまま*thisしてもよさそうだが、objのcopyを行い、obj自体をincrementするのが言語仕様なので
        //期待される振る舞いと異なる振る舞いにならないようにして値を返す
        Integer tmp(this->Value());
        ++value_;
        return tmp;
    }

    //copy: 戻り値はコピー先オブジェクト（自オブジェクト）の左辺値参照
    //コンストラクタとセットで使用。(普通は暗黙定義される)
    //参照を返すのは連続代入などで余計なコピーを行うと非効率であるため
    // a3 = a2 = a1を行っても参照を返せば問題はない
    // C++の代入演算子の戻り値の型は左辺値の型
    //★voidでも実装は可能だが連続代入ができなくなるので却下
    //参照型である理由は?
    //⇒メソッドチェーン。同じobjに対して複数のメソッドを連続して呼び出すのは、各メソッドが自身のobjの参照を戻り値として返すから
    //★c=b=aでcのcopyが結果だと、不要なコピーであるといえる。参照型を返した方が効率的
    //1.b=aでbはaをcopyし(defaultの場合、メンバの値をすべてコピーする)、そのあとでbの参照が返る(メソッドチェーンを行うため)
    //2.c=bでbの参照をもとに、cはbをcopyし、cの参照が返る
    //代入の場合は本来、自分が渡されたときの処理をする用がある⇒これは初期化にはない懸念点
    // Integer(const Integer &original){};
    // Integer& operator=(const Integer &original){

    // };

    // //move
    // Integer(Integer &&original){};
    // Integer& operator=(Integer &&original);


private:
    int value_;
};


//member関数の場合、objの指定はいらない
Integer operator-(const Integer &original){
    Integer tmp(-original.Value());
    return tmp;
}

int main(){
    Integer a(2);
    Integer b = -a;
    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
    cout << boolalpha << (typeid(a) == typeid(b)) << endl;
    cout << b.Value() << "\n"; //-2
    Integer c = a + b;
    cout << c.Value() << "\n"; //0
    c++;
    cout << c.Value() << "\n"; //1
    ++c;
    cout << c.Value() << "\n"; //2

    //初期化なので、コピーコンストラクタを使用
    Integer d = c;
    //代入なので、コピー代入演算子を使う(moveも一緒)
    b = c;
    //通常はもちろん定義はいらない。メモリを動的に割り当てるクラスにのみ使用

}
