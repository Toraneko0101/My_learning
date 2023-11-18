#include <bits/stdc++.h>
using namespace std;

long long N;
int main(){
    cin >> N;
    long long three = N / 3;
    long long five = N / 5;
    long long fifteen = N / 15;
    cout << three + five - fifteen << endl;
    return 0;
}