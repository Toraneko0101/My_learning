#include <bits/stdc++.h>
using namespace std;

int main(){
    int Q;
    cin >> Q;
    //priority_queueはheapで管理されている
    //最小をtopにする
    priority_queue<int, vector<int>, greater<int>> price;
    for(int i=0; i<Q; i++){
        int query;
        cin >> query;
        if(query == 1){
            int money;
            cin >> money;
            price.push(money);
        }
        else if(query == 2){
            cout << price.top() << endl;
        }
        else if(query == 3){
            price.pop();
        }
    }
    return 0;
}