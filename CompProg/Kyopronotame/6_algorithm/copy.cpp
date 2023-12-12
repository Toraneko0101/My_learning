#include <bits/stdc++.h>
using namespace std;

int main(){
    std::vector<int> v = {3,1,2};
    
    //普通にコピー(要素分は用意しておくこと)
    std::vector<int> v2(size(v));
    std::ranges::copy(v, v2.begin());

    //後ろに追加
    std::vector<int> other = {0,4};
    std::ranges::copy(v, std::back_inserter(other));
    
    //出力
    //要素をコピーするときに cout << x << ", "としてくれる
    std::ranges::copy(other, ostream_iterator<int>(cout, ", "));
    cout << "\n";
}