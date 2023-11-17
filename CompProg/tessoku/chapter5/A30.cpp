#include <bits/stdc++.h>
using namespace std;

int n,r;

// b ^ n (mod p)
long long powerMod(long long b, long long n, long long p){
    if(n==0) return 1;
    if(n==1) return b % p;
    if(n%2==1) return (b * powerMod(b, n-1, p)) % p;
    long long t = powerMod(b, n/2, p) % p;
    return (t * t) % p;
}

long long divMod(long long bunshi, long long bunbo, long long mod){
    // a/b = a * 1/b
    // modは素数なので,modにおいて
    // 1/b ≡ 1 * b^(x-2) 
    //powerMod = 繰り返し二乗
    return (bunshi * powerMod(bunbo, mod-2, mod) % mod);

}

int main(){
    long mod = 1e9 + 7;
    cin >> n >> r;
    
    //bunsi
    long long bunshi = 1;
    for(int i=1; i<=n; i++) bunshi = (bunshi * i) % mod;

    //bunbo
    long long expr1 = 1;
    for(int i=1; i<=r; i++) expr1 = (expr1 * i) % mod;
    long long expr2 = 1;
    for(int i=1; i<=(n-r); i++) expr2 = (expr2 * i) % mod;
    long long bunbo = expr1 * expr2 % mod;
    //divMod  bunsi / bunbo % mod;
    cout << divMod(bunshi, bunbo, mod) << endl;
    return 0;

}