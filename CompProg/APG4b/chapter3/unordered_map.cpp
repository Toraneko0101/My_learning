#include <bits/stdc++.h>
using namespace std;

int main(){
    //keyとしてpair,tupleなどのハッシュ関数が定義されていない型を使えない
    //loopで取り出される順番は定義されていない

    unordered_map<string,int> fruits;
    fruits["apple"] = 12;
    fruits["banana"] = 7;
    fruits["calamansi"] = 11;
    fruits["dragonfruit"] = 3;
    fruits["elephant_apple"] = 1;

    for(auto fruit : fruits){
        auto key = fruit.first;
        auto val = fruit.second;
        cout << format("{}:{}\n", key, val);
    }

    return 0;
}