#include <bits/stdc++.h>
using namespace std;

int W,H;
long long mod = 1e9+7;

long long powMod(long long b, long long n, long long p){
    if(n == 0) return 1;
    if(n == 1) return b % p;
    if(n % 2 == 1) return (b * powMod(b, n-1, p) % p);
    long long t = powMod(b, n/2, p);
    return (t*t) % p;
}

long long divMod(long long a, long long b, long long p){
    // a/b = a*1/b
    // a*1/b (mod p)
    //フェルマーの小定理より
    // a*b^(p-2) ≡ a*1/b (mod p)
    return (a * powMod(b, p-2, p) % p);
}


int main(){
    //最短経路は同じものを含む順列
    //(W+H)! / (W! * H!)
    cin >> W >> H;
    long long bunsi = 1;
    for(int i=1; i<=(W+H-2); i++){
        bunsi = (bunsi * i % mod);
    }

    long long bunbo = 1;
    long long expr1 = 1;
    long long expr2 = 1;
    for(int i=1; i<=W-1; i++) expr1 = expr1 * i % mod;
    for(int i=1; i<=H-1; i++) expr2 = expr2 * i % mod;
    bunbo = expr1 * expr2 % mod;

    cout << divMod(bunsi, bunbo, mod) << endl;
    return 0;


}