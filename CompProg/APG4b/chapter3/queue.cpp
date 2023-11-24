#include <bits/stdc++.h>
using namespace std;

int main(){
    queue<int> q;
    q.push(10);
    q.push(11);
    cout << q.front() << "\n";
    cout << q.back() << "\n";
    q.pop();
    cout << q.size() << "\n";
    q.pop();
    if(q.empty()) cout << "Yes" << "\n";
}