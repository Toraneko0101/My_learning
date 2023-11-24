#include <bits/stdc++.h>
using namespace std;

int main(){
    set<int> S;
    vector<int> A = {10,17,6,4,5,11,11,4};
    for(int a: A) S.insert(a);

    cout << "size: " << S.size() << "\n"; //6
    S.erase(4);
    if(S.count(4)) cout << "Yes" << "\n"; //No

    //空のSet以外なら最小と最大が取得可能
    cout << *begin(S) << endl; //最小
    cout << *rbegin(S) << endl; //最大

    //loop:小さいものから順に取り出される
    for(auto val: S) cout << val << " ";
    cout << endl;

    /**
     * 計算量
     * 値の追加、削除、所属 => logN
     * 要素数、最小、最大 => O(1)
    */
}