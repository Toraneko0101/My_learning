#include <bits/stdc++.h>
using namespace std;

int main(){
//stack
    int Q;
    cin >> Q;
    stack<string> box;
    for(int i=0; i<Q; i++){
        int query;
        cin >> query;
        if(query == 1){
            string book;
            cin >> book;
            box.push(book);
        }
        else if(query == 2){
            cout << box.top() << endl; 
        }
        else if(query == 3){
            box.pop();
        }
    }

    return 0;
}