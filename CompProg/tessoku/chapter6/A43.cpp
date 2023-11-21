#include <bits/stdc++.h>
using namespace std;

long long N, L;
long long A[200009];
char B[200009];
int main(){
    cin >> N >> L;
    for(int i=1; i<=N; i++) cin >> A[i] >> B[i];
    long long ans_max = 0;
    for(int i=1; i<=N; i++){
        if(B[i] == 'E') ans_max = max(ans_max, L - A[i]);
        else ans_max = max(ans_max, A[i]);
    }

    cout << ans_max << endl;
    return 0;

}