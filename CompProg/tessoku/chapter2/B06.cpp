#include <bits/stdc++.h>
using namespace std;


int main(){
    int N, Q;
    int A[100009], win[100009], lose[100009];
    int L[100009], R[100009];

    cin >> N;
    for(int i=1; i<=N; i++) cin >> A[i];
    cin >> Q;
    for(int i=1; i<=Q; i++) cin >> L[i] >> R[i];

    for (int i=1; i<=N; i++){
        if(A[i]){
            win[i] = win[i-1] + 1;
            lose[i] = lose[i-1];
        }else{
            win[i] = win[i-1];
            lose[i] = lose[i-1] + 1;
        }
    }

    int win_count, lose_count;
    for (int i=1; i<=Q; i++){
        win_count = win[R[i]] - win[L[i]-1];
        lose_count = lose[R[i]] - lose[L[i]-1];
        if (win_count > lose_count){
            cout << "win" << endl;
        }else if(win_count == lose_count){
            cout << "draw" << endl;
        }else{
            cout << "lose" << endl;
        }
    }
    return 0;

}