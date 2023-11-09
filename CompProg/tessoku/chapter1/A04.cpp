#include <bits/stdc++.h>
using namespace std;

int N;

int main(){
    cin >> N;
    //各桁を求めたいので%2する。
    for(int i=9; i>=0; i--){
        int mul = (1 << i);
        cout << (N / mul) % 2;
    }
    cout << endl;
    return 0;
}