#include <bits/stdc++.h>
using namespace std;

long long A,B;

int main(){
    cin >> A >> B;
    long long div = gcd(A,B);
    long long mul =  A / div * B;
    cout << mul << endl;
}