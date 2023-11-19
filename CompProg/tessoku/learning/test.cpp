#include <bits/stdc++.h>
using namespace std;

int main() {
   int a = 200000;
   long long b;
   b = a;
   long long ans = 0;
   ans += (b * (b-1) * (b-2) /6);
   cout << ans << endl;
}