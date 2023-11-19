#include <bits/stdc++.h>
using namespace std;
//下限値を考える
int D, N;
int L[10009];
int R[10009];
int H[10009];
int max_work[10009] = {0};
int main(){
    cin >> D >> N;
    for(int i=1; i<=N; i++) cin >> L[i] >> R[i] >> H[i];
    for(int i=1; i<=D; i++) max_work[i] = 24;

    //query
    for(int i=1; i<=N; i++){
        //date
        for(int j=L[i]; j<=R[i]; j++){
            max_work[j] = min(H[i], max_work[j]);
        }
    }
    int ans = 0;
    for(int i=1; i<=D; i++){
        ans += max_work[i];
    }
    cout << ans << endl;
    return 0;
}