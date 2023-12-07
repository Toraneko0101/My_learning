/**
 * 例外はコーディング規約によっては禁止されているとか
 * 
 * 例外にはあらゆる型が使用可能
 * try{
 *  throw 123;
 * }catch (const int v){
 *  cout << v << endl;
 * }
 * 
 * 例外の型がクラスである場合にはアップキャストを含めて補足する
 * 補足は最初に一致したものだけが処理される
 * 
 * catch(...)
 * とするとあらゆる例外を補足可能
 * 
 * 関数内で例外が補足されない場合
 * ⇒関数内にtry節がない場合、補足するまで呼び出し元をたどっていく
 * ⇒関数内にthrowを書けば、tryブロック内には一見throwがないように見える
 * ※送出された例外が補足されない場合、std::terminateが呼び出され、プログラムは異常終了する
 * 
 * noexcept
 * 関数が例外を送出しないことを明示的に示す
 * デストラクタなどは暗黙的にnoexcept
 * noexcept(true)なら例外を送出しない
 * noexcept(false)なら送出する
 * noexcept内でnoexceptを使用した場合、他の関数がnoexceptであるかどうかを条件に指定可能
 * ⇒ int StringToInt(const string& str) noexcept(noexcept(CharToInt(char())))
 * ⇒noexcept指定された関数から例外が送出されたらterminate
 * 
 * ※関数から送出される例外を列挙するthrowキーワードは削除された
 * int CharToInt(const char c) throw(runtime_error):
 * 
 * 例外クラスの紹介
 * std::exception
 *  全ての標準ライブラリの例外クラスの基底
 * std::logic_error
 *  論理エラー。標準ライブラリで出すものはない
 * std::invalid_argument
 *  関数の実引数が不正。変換できない文字列の指定など
 * std::out_of_range
 *  at()による範囲外参照。おなじみ
 * []の場合、Segmentation faultが見えたりする
 * std::bad_cast
 *  dynamic_castで失敗した時に見る
 * std::runtime_error
 *  実行時エラー。
 * 
 * デストラクタと例外
 *  例外を送出⇒補足するまでの間に例外送出
 *  これは許可されず、std::terminateによる異常終了となる
 *  デストラクタから例外を投げるとちょうどそうなる
 * 　⇒例外を送出すると、例外が補足されるより前に
 *     更にデストラクタから例外を送出する羽目になる
 * ⇒そもそも例外を投げると、リソースの解放がうまくできなくなる可能性があるのでやってはいけない
 * 
*/
#include <bits/stdc++.h>
using namespace std;

int error_func(){
    throw 123;
}

int Compare(int a, int b) noexcept{
    if(a < b) return -1;
    else if(a > b) return 1;
    else return 0;
}

int main(){
    string str("123XY56");
    try{
        auto isNumber = [](string str){
            for(const auto s: str){
                if(std::isdigit(s) == 0) return false;
            }
            return true;
        };

        bool result = isNumber(str);
        if(!result){
            throw std::runtime_error("数値ではない文字が入っています");
        }
        cout << stoi(str) << "\n";
    }catch(const std::runtime_error& e){
        //.what()でerror messageを取得
        cout << e.what() << endl;
    }catch(const std::exception& e){
        cout << "役に立たないハンドリングだよ" << endl;
    }catch(...){
        cout << "unexpected exception was thrown" << endl;
    }

    //関数内でthrow
    try{
        error_func();
    }catch(const int v){
        cout << v << endl;
    }

    std::vector<int> vec = {1,2,3,4,5};
    try{
        vec.at(10);
    }catch(const std::out_of_range& e){
        cout << "例外取得：" << e.what() << "\n";
    }
}