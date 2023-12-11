#include <bits/stdc++.h>
using namespace std;

int main(){
    //初期化
    long long N, ans;
    vector<int> A;
    // 0 ~ 199を0で初期化
    vector<int> two_handred(200,0);
    
    //入力
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> A.emplace_back();
    }

    //余り
    for(auto a : A){
        int mod = a % 200;
        two_handred.at(mod) += 1;
    }

    //cnt
    for(long long t: two_handred){
        if(t <= 1) continue;
        //nC2
        ans += t * (t - 1) / 2; //int型だとoverflowするので注意
    }
    cout << ans << endl;
}