#include <bits/stdc++.h>
using namespace std;

int main(){
    stack<int> s;
    //先入れ後出し
    s.push(10);
    s.push(1);
    s.push(3);
    //.top()は最後に追加した値
    while(!s.empty()){
        cout << s.top() << "\n";
        s.pop();
    }
}