/**
 * std::string以外の
 * <string>ヘッダの機能
*/

#include <bits/stdc++.h>
using namespace std;

int main(){
    //数値- -> string(精度の指定は不可)
    int n = 10;
    string s1(to_string(n));
    //文字列 -> 整数
    unsigned long long n1 = std::stoull(s1);
    cout << n1 << endl;

    //特定の進数に直す: stoi(str, nullptr, base)
    string s3 = "111";
    int n3 = stoi(s3, nullptr, 2);
    cout << n3 << endl;
    string str_dec = "2001, A Space Odyssey";
    string::size_type sz; //stringの要素数とidxを示す
    int i_dec = std::stoi (str_dec,&sz);
    cout << i_dec << "[" << str_dec.substr(sz) << "]\n";

    

}