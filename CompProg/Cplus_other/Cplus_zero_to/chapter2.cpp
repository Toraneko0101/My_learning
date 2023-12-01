//新しく覚えた箇所だけ
#include <bits/stdc++.h>
using namespace std;

/**
 * 2-1 ~ 2-2
 * gccではintは32,longは64
 * 
 * charがsinged charになるかunsigned charになるかは処理系定義による
 * コンパイラオプションなどで選択できたり
 * 移植性を重視したい場合は、
 * std::int32_tやstd::int64_t
 * std::uint8_t等を使う
 * サイズ指定付き整数型は#include <cstdint>で使える
 * 
 * enum
 * 数値型にenumの値を代入は可能
 * enumに直接数値を代入することはできない
 * Day day = 5;のような事は無理。
 * 列挙子の名前を被らせてはいけない
 * たとえばenum Dayの中でSunを使ったら、違う列挙体の中でSunは使えない
 * 
 * enum
 * 名前をかぶらせたい場合、こっち
 * ただし、enum classの場合、数値型に入れるには明示的な型変換が必要
 * キャストについてはmain内に記載
 * 
*/

enum Day{
    //default=0, 値を指定すると次は++
    Sun = 1,
    Mon,
    Tue,
    Wed = 11,
    Tru,
    Fri,
    Sat
};

enum class Test1{
    one = 1,
    two,
    three
};
enum class Test2{
    one = 101,
    two,
    three
};

std::int32_t x1 = 10;

int Add(int x){
    return x * 2;
}
int Add(int x, int y){
    return x + y;
}
int main(){
    int x = Fri;
    Day day = Fri;
    cout << day << "\n";
    Test1 test1 = Test1::one;
    //整数型に明示的にキャストする必要があるのでエラーになる
    //列挙型の値を直接coutには出力できない
    //ユーザ定義型の場合operator<<が必要
    //cout << test1 << "\n";
    /**
     * 2-2
     * キャスト
     * Cスタイルのキャストは (int)x
     * ただしこれは、static_cast, reinterpret_cast, const_cast, dynamic_castのいずれかを指すという意味になる
     * コンパイラはすべてのキャストを試し、動作するとやめる
     * つまり、期待したキャストが選ばれない可能性があり、バグの温床になる
     * 
     * static_cast<int>(x)
     * これはstatic_castというC++のキャスト演算子を使用している
     * コンパイル時に型変換を行い、型変換が適切であることをコンパイラがチェックする
     * つまり、型変換が不適切である場合にコンパイラエラーを出してくれる
    */
    cout << static_cast<int>(test1) << "\n";

    /**
     * 整数リテラル
     * 032 //8進数
     * 0x1a //16進数リテラル(大文字小文字区別されない)
     * 26u unsigned
     * 26l long
     * 26ul unsigned long
     * 0x1All long long型の0x1A
    */

   /**
    * 2-3 ポインタと参照
    * C++03などではヌルポインタを示すのにNULLを使っていた
    * これはCから引き継いだもので
    * Cではvoid*型の変数は任意のポインタ型に暗黙変換される仕様があるので
    * NULLを(void*)0と定義している例が見られた
    * しかしC++ではそのような暗黙変換は許容されていないのでNULLは0とされていた
    * しかし、0はヌルポインタだったり、int型とみなされたりと不都合が多いのでnullptrが導入された
   */
    int *p = nullptr;
    //constポインタ
    int x1 = 123;
    //const int*とすると、ポインタが指し示す値が不変
    const int* p1 = &x1;
    //int* constとすると、ポインタ自身の書き換えが不可
    int* const p2 = &x1;
    *p2 = 246;
    //p2 = nullptr //error
    cout << x1 << endl;

    //参照
    int x2 = 100;
    int *p3 = &x2; //ポインタの宣言
    int &r = x2; //参照型。rを付けるだけで、値にアクセスする際も*とデリファレンスしなくていいし、元値に何もつけなくていいので楽。
    r = 200;
    cout << x2 << endl;

    //2-5. コメント
    //入れ子にして使うことはできない

    //2-6. 制御文(初期値指定したもの)
    switch(auto i = 1; i){
        case 1:
            cout << "neko\n";
            [[fallthrough]]; //現在のコンパイラはフォールスルー動作に対する警告は出さないので、コードを読む人向けにこの動作が意図的だと言っているようなもん
        case 2:
            cout << "please print\n";
            break;
        default:
            break;
    }

    //制御文をmapで模倣
    /**
     * 複数種類の関数をラップして同じように扱う
     * std::function<戻り値の型(引数の型)>　obj
     * obj(args)で使う。
    */
    unordered_map<string, function<void()>> actions = {
        {"one", [](){cout << 1 << "\n"; }},
        {"two", [](){cout << 2 << "\n"; }},
        {"three", [](){cout << 3 << "\n"; }}
    };


    string test_strs[] = {"one", "two", "three", "four"};
    for(auto str : test_strs){
        if(actions.contains(str)) actions[str]();
        else cout << "other number\n";
    } 

    //2.7 演算子
    //後置デクリメントは、他の処理を行ってからデクリメント
    //前置デクリメントは、デクリメントしてから処理
    int a = 5; int b = 0;
    int c = 5; int d = 0;
    b = a++; //代入してからincrement
    cout << a << endl; //6
    cout << b << endl; //5
    d = ++c; //incrementしてから代入
    cout << c << endl; //6
    cout << d << endl; //6

    //bit演算をするときはunsignedの方がいい
    cout << bit_ceil(9u) << endl; //16
    //基数のプレフィックスを出力 + 16進法で出力
    cout << std::showbase << std::hex; 
    unsigned int a1 = 0x0000000f; //15
    cout << ~a1 << endl; //0xfffffff0;
    cout << std::noshowbase << std::dec; //表記を戻す
    cout << a1 << endl; //15

    //代入演算子は、復号代入の場合も算術演算子より後に解釈

    //2.8 コマンドライン引数
    /**
     * int main(int argc, char* argv[])
     * int argc
     *  コマンドライン引数の個数
     * char* argv[]
     *  コマンドライン引数が格納される
    */

    //関数ポインタ
    /**
        * s関数ポインタを変数に代入する際はautoを使うと簡略化が可能
    */
    //関数Addのアドレスを保持するが、その際にオーバーロードを解決する
    //引数無しでも区別できるようにするために
    int (*fp)(int, int) = Add; 
    int result = fp(3,5);
    cout << result << "\n";
    cout << Add(3,5) << "\n";
    cout << Add(4) << "\n";

    //2.9 ラムダ式
    /**
     * 生成される関数objはautoで保持する
     * ラムダ式の外にある変数をラムダ式の中で使用する場合は先頭の[]でキャプチャを指定する
     * [=] ラムダ式定義時に存在するすべての変数をコピーして使う
     * [&] ラムダ式定義時に存在するすべての変数を参照してて使う
     * [a] 変数aをcopy
     * [&a] 変数aを参照
     * [=, &a] 変数aは参照。それ以外はcopy
     * 戻り値の明示 ->intは、型推論に任せる場合は省略可能
    */
    auto func = [](int a, int b) ->int {return a + b;};
    int result1 = func(4,6);
    cout << result1 << endl;

    /**
     * コピーキャプチャされた変数は暗黙的にconstとなる
     * コピーした値を変更したい場合はmutableキーワードを使用する
     * その場合、ラムダ式の関数呼び出し演算子はconst-by-valueとなる
    */
    int init = 5;
    //auto f = [init](int a, int b){init++; return init + a*b;}; //readonly関連のエラー
    auto f = [init](int a, int b) mutable{init++; return init + a * b;};
    auto g = [&init](int a, int b){init++; return init + a*b;};
    cout << f(2,4) << endl;
    cout << init << endl;
    cout << g(2,4) << endl;
    cout << init << endl;

    //キャプチャを持たないラムダ式なら関数ポインタに暗黙変換可能
    int (*fpr)(int, int) = [](int x, int y){return x+y;};
    cout << fpr(3,4) << "\n";

    //std::function
    //関数ポインタの型があいまいだとオーバーロードを解決できず、エラーを吐く。そのためキャスト
    std::function<int(int)> f1 = static_cast<int(*)(int)>(Add);
    // std::function<int(int)> f1 = Add;
    
  std::function<int(int, int)> f2 = static_cast<int(*)(int, int)>(Add);  // std::function<int(int, int)> f2 = Add;
    int result2 = f2(3,9);
    cout << result2 << "\n";
    f2 = [](int x, int y){return x*y;};
    cout << f2(7,11) << endl;

    /**
     * for文の構造
     * 1. ループ前に初期化式の実行
     * 2. ループ開示時に条件式評価。falseなら抜ける
     * 3. ループ式が最後に実行。
     * つまり,for(int i=0; i++ < 10;)のような書き方をすると、
     * increment後に抜ける判定をすることにするので挙動が変わる。
     * 
    */

   /**
    * 後置と前置の速度の差について
    * 現代のコンパイラなら最適化optionを入れていれば同等のアセンブリが出力されるとのこと
    * 結果が変わらない場合は、コードスタイルに合わせればいい
    * ⇒★gcc -Sでコンパイルしてループの部分を後で比較してみる
   */



}
