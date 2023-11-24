#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<string> words = {"apple", "banana", "calamansi"};
    /**
     * 順に各要素への参照(変更しない場合は const auto& )
     * 配列の要素数を変えないこと
     * words.push_back("hoge")などは厳禁
    */
   //初期化ベースの範囲for
    for(size_t i = 0; auto& word: words){
        //push_backなのでchar(一文字)のみ許される
        word.push_back('!');
        cout << i << ":" << word << "\n";
        i++;
    }

    //イテレータ(複雑になるので非推奨)
    for(auto it = words.begin(); it != words.end(); it++){
        cout << *it << "\n";
    }

    //逆イテレータ
    //end()は最後の要素の次を返すので、
    //end(), begin() it--のようなコードはうまく動かない
    for(auto it= words.rbegin(); it != words.rend(); it++){
        cout << *it << "\n";
    }
}