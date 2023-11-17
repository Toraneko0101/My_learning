#include <bits/stdc++.h>
using namespace std;

int Q;
int X[10009];

int main(){
    //計算時間 10**4 * O(√300000) ≒ 10**6 * 5
    cin >> Q;
    for(int i=1; i<=Q; i++) cin >> X[i];
    for(int i=1; i<=Q; i++){
        int num = X[i];
        int root = (int)sqrt(num);
        bool is_prime = true;
        for(int i=2; i<=root; i++){
            if(num % i == 0) is_prime = false;
        }

        cout << (is_prime ? "Yes" : "No") << endl;
    }
    return 0;
}