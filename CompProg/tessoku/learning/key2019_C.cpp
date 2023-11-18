#include <bits/stdc++.h>
using namespace std;

int N;
long long A[100'009];
long long B[100'009];

int main(){
    cin >> N;
    for(int i=1; i<=N; i++) cin >> A[i];
    for(int i=1; i<=N; i++) cin >> B[i];


    // A[i] < B[i]の総和
    long long minus_S = 0;
    // A[i] < B[i] の個数
    long long minus_C = 0;
    // A[i] > B[i]の総和
    long long plus_S = 0;
    vector<long long> plus;
    for(int i=1; i<=N; i++){
        if(A[i] > B[i]){
            plus.push_back(A[i] - B[i]);
            plus_S += A[i] - B[i];
        }
        if(A[i] < B[i]){
            minus_S += B[i] - A[i];
            minus_C ++;
        }
    }

    //minusの方が大きい場合無理。
    if(minus_S > plus_S){
        cout << -1 << endl;
        return 0;
    }

    //破壊的(昇順なのでpop_backする)
    sort(plus.begin(), plus.end());

    while(minus_S > 0){
        long long buf = plus.back();
        plus.pop_back();
        minus_S -= buf;
        minus_C ++;
    }

    cout << minus_C << endl;
    return 0;
}