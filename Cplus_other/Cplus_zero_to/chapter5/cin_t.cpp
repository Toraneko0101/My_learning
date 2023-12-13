#include <iostream>
#include <format>
using namespace std;

int main(){
    cout << "標準出力" << "\n";
    /**
     * std::endl: 改行
     * std::cout: 標準出力
     * std::cin: 標準入力
     * std::ceer: 標準エラー出力
    */
   cerr << "標準エラー出力" << "\n";
   // ./a.out 2> error.txt > normal.txt

   int num;
   //読み込み成否をif文で判断
   cout << "整数を入力してください";
   if(cin >> num) cout << format("入力した整数は{}です", num) << "\n";
   else cout << "不正な入力です" << "\n";

}