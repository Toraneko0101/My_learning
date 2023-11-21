#include <bits/stdc++.h>
using namespace std;

//reverseがきついのでstateを持つ
int N,Q;
int A[200009];
int state = 1; //1 front, 2 reverse
int main(){
    cin >> N >> Q;
    for(int i=1; i<=N; i++) A[i] = i;

    for(int i=1; i<=Q; i++){
        int query;
        cin >> query;
        if(query == 1){
            int x,y;
            cin >> x >> y;
            if(state == 1) A[x] = y;
            else A[N-x+1] = y;
        }
        else if(query == 2){
            state *= -1;
        }
        else{
            int x;
            cin >> x;
            if(state == 1) cout << A[x] << endl;
            else cout << A[N-x+1] << endl; 
        }
    }
    return 0;
}