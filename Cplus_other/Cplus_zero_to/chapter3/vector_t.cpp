/**
 * vectorは要素アクセス、末尾に対する追加削除に用いる
 * 末尾以外に対する挿入削除は、deque, listに劣る
 * capacityは常にsize() <=
 * しかし領域の再確保には時間がかかるのでreserve()をするのも手
 * 
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> vec;
    vector<int> another_vec(3, 10);
    for(auto i: {2,4,5,1,9}){
        //要素の生成をコンテナ内部で行う
        vec.emplace_back(i);
    }
    vec.emplace(vec.begin() + 2, 7);
    for(auto i : views::reverse(vec)){
        cout << i << " ";
    }cout << "\n";
    vec.swap(another_vec); //swap
    cout << vec.at(0) << "\n";
}