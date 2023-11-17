#include <bits/stdc++.h>
using namespace std;

long long a,b;
long long mod = 1e9 + 7;
long long modPow(long long a, long long b, long long mod){
    long long P = a, Answer = 1;
    for(int i=0; i<30; i++){
        int div = (1 << i);
        //a^11 = a^8 * a^2 * a^1
        if((b / div) % 2 == 1) Answer = (Answer * P) % mod;
        P = (P * P) % mod;
    }

    return Answer;
}

int main(){
    //累乗の数が10**9まであるのでpowではだめ
    cin >> a >> b;
    //繰り返し二乗(一応0乗にも対応)
    cout << modPow(a,b,mod) << endl;
    return 0;
}