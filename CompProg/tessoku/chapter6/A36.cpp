#include <bits/stdc++.h>
using namespace std;

long long N, K;
int main(){
    cin >> N >> K;
    if(K < 2 * N - 2){
        cout << "No" << endl;
        return 0;
    }
    if(K % 2 != 0){
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
    return 0;
}