#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> A(1,INT_MIN);
    for(int i=0; i<3; i++) cin >> A.emplace_back();
    std::ranges::sort(A);
    if(
        (A.at(3) - A.at(2)) == (A.at(2) - A.at(1))
    )cout << "Yes" << "\n";
    else cout << "No" << "\n";
}