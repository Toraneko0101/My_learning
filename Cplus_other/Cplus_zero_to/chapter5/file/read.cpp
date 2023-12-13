/**
 * 読み込み
 * std::ifstream
*/

#include <bits/stdc++.h>
using namespace std;

int main(){
    ifstream file("in.txt");
    string line;
    vector<string> vec;
    while(getline(file, line)){
        vec.emplace_back(line);
    }

    for(auto v: vec) cout << v << endl;
}
