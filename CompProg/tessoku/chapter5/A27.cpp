#include <bits/stdc++.h>
using namespace std;

int A,B;

int gcd_calc(int A,int B){
    if(B == 0) return A;
    return gcd_calc(B, A%B);
}


int main(){
    cin >> A >> B;
    //int ans = gcd(A,B);
    int ans = gcd_calc(A,B);

    cout << ans << endl;
}