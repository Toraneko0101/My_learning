#include <bits/stdc++.h>
using namespace std;

int main(){
    //viewはアクセス方法を変更するだけ
    //コストは最小になる

    //std::views::reverseで逆順,実際には並び替えない
    vector<string> words = {"zero", "one", "two", "three", "four", "five"};

    //逆順アクセス
    for(const auto& word : words | views::reverse){
        cout << word << "\n";
    }
    cout << "---" << endl;

    //最初のN個の要素にアクセス(N未満ならすべて)
    for(const auto& word: words | views::take(3)){
        cout << word << "\n";
    }
    cout << "---" << endl;

    //最初のN個の要素を除いた要素にアクセス(N未満なら空)
    for(const auto& word: words | views::drop(4)){
        cout << word << "\n";
    }
    cout << "---" << endl;

    //最初のN個の要素を除いた後、最初のM個の要素にアクセス
    for(const auto& word: words | views::drop(2) | views::take(2)){
        cout << word << "\n";
    }
    cout << "---" << endl;

    //※viewを作る際にはパイプが使える

    //3番目の要素から2個の要素にアクセス:views::counted(it, count)を使う
    for(auto& word : views::counted((words.begin() + 3), 2)){
        cout << word << endl;
    }
    cout << "---" << endl;

    //viewsをvectorに変換
    auto view = (words | views::take(3));
    vector<string> words2(view.begin(), view.end());
    for(const auto& word : words2) cout << word << endl;
    cout << "---" << endl;

    //c++23からはranges::to<vector>()が使えるらしい
    //views to vector
    
}