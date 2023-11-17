#include <bits/stdc++.h>
using namespace std;

int N;
bool is_prime[1'000'009];

int main(){
    cin >> N;
    int root = (int)sqrt(N);
    for (int i=1; i<=N; i++) is_prime[i] = true;
    is_prime[1] = false;
    for(int i=2; i<=root; i++){
        if(is_prime[i] == false) continue;
        for(int j=i*2; j<=N; j+=i){
            is_prime[j] = false;
        }
    }

    for(int i=1; i<=N; i++){
        if(is_prime[i] == true) cout << i << endl;
    }
    return 0;
}