#include <bits/stdc++.h>
using namespace std;

int main(){
    int Q;
    cin >> Q;
    queue<string> human;
    for(int i=0; i<Q; i++){
        int query;
        cin >> query;
        if(query == 1){
            string name;
            cin >> name;
            human.push(name);
        }
        else if(query == 2){
            cout << human.front() << endl;
        }
        else if(query == 3){
            human.pop();
        }
    }
    return 0;
}