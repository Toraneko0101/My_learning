#include <bits/stdc++.h>
using namespace std;

long long a,b,c;


int main(){
    cin >> a >> b >> c;
    long long ans;
    ans = a + b + c;
    if(ans == 0) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}