#include <bits/stdc++.h>
using namespace std;

int main(){
    //最小、最大の取り出しは不可能
    //定数倍の関係で、実際の速度がsetとは限らない
    vector<int> v = {1,7,6,8,10,9,4,3,2,1};
    unordered_set<int> s(v.begin(), v.end());

    cout << s.size() << "\n";
    return 0;

}