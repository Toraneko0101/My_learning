#include <bits/stdc++.h>
using namespace std;

long long N;
int main(){
    cin >> N;

    long long three = N / 3;
    long long five = N / 5;
    long long seven = N / 7;
    long long three_five = N / 15;
    long long three_seven = N / 21;
    long long five_seven = N / 35;
    long long all = N / 105;

    long long ans = three + five + seven - three_five - three_seven - five_seven + all;
    cout << ans << endl;
    return 0;

}