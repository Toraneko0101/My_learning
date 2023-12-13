#include <bits/stdc++.h>
using namespace std;

int main(){
    int N; cin >> N;
    vector<int> A(1);
    vector<int> B(1);
    vector<int> C(1);

    for(int i=0; i<N; i++) cin >> A.emplace_back();
    for(int i=0; i<N; i++) cin >> B.emplace_back();
    for(int i=0; i<N; i++) cin >> C.emplace_back();

    vector<int> condition(1e5 + 9, 0);

    //Cに紐づいたBだけ入れる
    for(int i = 0; auto c : C){
        if(i == 0){
            i++;
            continue;
        }
        condition.at(B.at(c))++;
        i++;
    }

    //A == B_C_jを探索
    long long ans = 0;
    for(auto a : A){
        ans += condition.at(a);
    }
    cout << ans << endl;

}