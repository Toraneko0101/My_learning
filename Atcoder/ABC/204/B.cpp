#include <bits/stdc++.h>
using namespace std;

int main(){
    int N;
    vector<int> A(1,0);
    cin >> N;
    for(int i=1; i<=N; i++){
        cin >> A.emplace_back();
    }

    int ans = 0;
    for(int i=1; i<=N; i++){
        if(A.at(i) <=10 ) continue;

        ans += A.at(i) - 10;
    }
    cout << ans << endl;
}