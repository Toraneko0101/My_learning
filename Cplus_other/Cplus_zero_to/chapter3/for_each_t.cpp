#include <bits/stdc++.h>
using namespace std;

int main(){
    /**
     * foreach
     * [first, last)に指定された関数を適用する
     * ただ出力するならsizeとfor文でもいい気がするが
    */
    int ar[] = {4,5,6};
    for_each(std::begin(ar), std::end(ar), [](int x){cout << x << " ";});
    cout << "\n";
    for(int i=0; i<size(ar); i++) cout << ar[i] << " ";
    cout << "\n";

    //vecの出力
    vector<int> vec;
    for(auto i: views::iota(0,10)) vec.emplace_back(i);
    for(auto i: vec) cout << i << " ";
    cout << "\n";
    //統一した記述ができるのはいいかも
    for_each(vec.begin(), vec.end(), [](int x){cout << x << " ";});
    cout << "\n";
}