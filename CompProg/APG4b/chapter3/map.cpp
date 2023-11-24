#include <bits/stdc++.h>
using namespace std;

int main(){
    //連想配列
    map<string, int> fruit;
    fruit["apple"] = 3; //追加
    fruit["calamansi"] = 4;
    fruit["dragonfruit"] = 7;
    fruit["emblica"] = 4;
    fruit.erase("apple"); //消去
    //所属判定
    if(fruit.count("banana") == false){
        fruit["banana"] = 4;
    }
    cout << fruit.at("banana") << "\n"; //アクセス
    cout << fruit.size() << "\n"; //要素数

    //loop(追加順ではなく、pairの比較順で取り出される)
    for(pair<string, int> f: fruit){
        string key = f.first;
        int val = f.second;
        cout << format("{}:{}\n", key, val);
    }
    //loop:auto
    for(auto f: fruit){
        auto k = f.first;
        auto v = f.second;
        cout << format("{}:{}\n", k, v);
    }

    //計算量はsize以外、logN
    //keyの順番が要らないならunordered_mapの方が優れている
    /**
     * map: 平衡二分探索木 => O(logN)
     * unordered_map:ハッシュテーブル => O(1)
    */

}