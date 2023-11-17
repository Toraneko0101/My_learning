#include <iostream>
using namespace std;

long long modPow(long long a, long long b, long long mod){
    if(b==0) return 1;
    if(b==1) return a % mod;
    //端数用
    if(b % 2 == 1) return (a * modPow(a,b-1,mod)) % mod;
    long long P = modPow(a, b/2, mod);
    return (P * P) % mod; //a^8 = a^4 * a^4
}

int main(){
    long long a, b;
    cin >> a >> b;
    cout << modPow(a,b,1e9+7) << endl;
    return 0;
}