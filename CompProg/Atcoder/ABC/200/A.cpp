#include <bits/stdc++.h>
using namespace std;

int main(){
    /**
     * 1 <= N <= 3000
    */
    int N;
    int century;
    cin >> N;
    century = (N / 100) + 1;
    if(N % 100 == 0) century -= 1;
    cout << century << "\n"; 
}