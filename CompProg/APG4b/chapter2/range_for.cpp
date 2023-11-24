#include <bits/stdc++.h>
using namespace std;

//C++20からindex指定可能に
//"cpp": "cd $dir && g++ -std=c++20 $fileName -o a.out && ./a.out",
int main(){
    vector<int> a = {1,3,2,5};
    for(size_t i = 0; int x : a){
        if(x == 5) break;
        cout << "index:" << i << " " << "value:" << x << endl;
        i++;
    }
}