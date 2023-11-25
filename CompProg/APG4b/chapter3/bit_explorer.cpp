#include <bits/stdc++.h>
using namespace std;

//本来は動的計画するけど
int main(){
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for(int i=0; i<N; i++) cin >> A.at(i);

    bool ans = false;
    for(int tmp = 0; tmp <(1<<20); tmp++){
        bitset<20> s(tmp);

        int sum = 0;
        for(int i=0; i<N; i++){
            if(s.test(i)) sum += A.at(i);
        }
        if(sum == K) ans = true;
    }

    if(ans) cout << "Yes" << "\n";
    else cout << "No" << "\n";
    return 0;
}