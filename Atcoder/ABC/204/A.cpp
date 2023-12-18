#include <bits/stdc++.h>
using namespace std;

int main(){
    int x, y; cin >> x >> y;
    if(x == y){
        cout << x << endl;
    }else{
        vector<int> a = {0,1,2};
        std::erase(a, x);
        std::erase(a, y);

        cout << a.at(0) << endl;
    }
}