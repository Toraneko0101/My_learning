//bit和
#include <bits/stdc++.h>
using namespace std;

//N枚のカードの中から選び、書かれた整数の合計がKとなるようにする方法が存在するか?
int main(){
    int N,K, A[22];
    cin >> N >> K;
    for (int i=1; i <=N; i++) cin >> A[i];

    bool ans = false;
    for (int i = 0; i < (1 << N); i++){
        int sum = 0;
        //j番のcardを使うか
        for(int j = 1; j <= N; j++){
            int wari = (1 << (j - 1));
            if ((i / wari) % 2 == 1) sum += A[j]; 
        }
        if (sum == K) ans = true;
    }

    if (ans) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}