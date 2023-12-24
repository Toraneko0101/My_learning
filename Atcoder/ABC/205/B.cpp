#include <bits/stdc++.h>
using namespace std;

int main(){
    // popすればよさそう
    int N;
    cin >> N;
    vector<int> A;
    for (int i = 0; i < N; i++)
        cin >> A.emplace_back();

    std::ranges::sort(A);
    for(int i=1; auto a: A){
        if(i != a){
            cout << "No" << endl;
            return 0;
        }
        i++;
    }
    cout << "Yes" << endl;
}