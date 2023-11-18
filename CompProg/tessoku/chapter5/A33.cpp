#include <bits/stdc++.h>
using namespace std;

int N;
int A[100'009];
int main(){
    cin >> N;
    for(int i=1; i<=N; i++) cin >> A[i];

    int ansbit = A[1];
    for(int i=2; i<=N; i++){
        ansbit ^= A[i];
    }

    //0でない場合
    if(ansbit) cout << "First" << endl;
    else cout << "Second" << endl;
    return 0;
}