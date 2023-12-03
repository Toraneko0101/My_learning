/**
 * vector<int> x(100000);
 * vector<int> y = x; //100000分のメモリを確保しておりもったいない
*/

/**
 * ムーブについてはmake_uniqueのstd::moveで説明した
*/

/**
 * 右辺値と左辺値
 * int x = 300; //xは左辺値。300は右辺値
 * int y = functon(); functionが返す一時objectは右辺値
 * int z = x; zとxは左辺値
 * 
 * 右辺値は、左辺値へ格納したら必要なくなる
 * つまり、右辺値にはムーブの考え方が適用可能
*/

/**
 * std::move
 * 
 * vector<int> x(100000);
 * vector<int> y = x; //この場合、yとxは左辺値
 * つまり、代入時にdeepcopyされる
 * そのため、左辺値xを右辺値へキャストする
 * 右辺値を参照するときは、&&をつける
 * int &&x = 100;
 * 
 * ※左辺値の参照と右辺値の参照は別の型とされる
 * そのためoverloadを使用して、引数が左辺値参照と右辺値参照で処理の分け分けが可能
 * 
 * ムーブ後の変数は、スマートポインタならnullptr
 * そのほかでも、同じものが複数存在しないという制約を持つクラスなら無効値となる
*/
#include <bits/stdc++.h>
using namespace std;

void Print(string&){
    cout << "左辺値参照" << "\n";
}

void Print(string&&){
    cout << "右辺値参照" << "\n";
}


int main(){
    vector<int> x(100000);
    vector<int> y = std::move(x); //xは右辺値

    string str("hoge");
    Print(str);
    /**
     * std::moveはこれ以降objを使わないという明示
     * 実際のムーブはstd::move()に通し、
     * ムーブコンストラクタ・ムーブ代入演算子に渡した際に行われる
     * そのためstd::move(str)としてもキャストするだけで何も起こらない
    */
    Print(std::move(str)); 
    //std::move(str); //nodiscard
    //cout << str << "\n";
    
    string str1 = std::move(str);
    //cout << str << "\n"; //空,std::moveの後、代入すれば空になるっぽい
}