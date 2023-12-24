#include <bits/stdc++.h>
using namespace std;

int main(){
    int A, B, C;
    cin >> A >> B >> C;

    if(A >= 0 && B >= 0){
        if(A > B) cout << ">" << "\n";
        else if(A < B) cout << "<" << "\n";
        else cout << "=" << "\n";
    }else if(A < 0 && B >= 0){
        if(C % 2 == 0){
            if(abs(A) > B) cout << ">" << "\n";
            else if(abs(A) < B) cout << "<" << "\n";
            else cout << "=" << "\n";
        }else{
            cout << "<" << "\n";
        }
    }else if(A >= 0 && B < 0){
        if(C % 2 == 0){
            if(A > abs(B)) cout << ">" << "\n";
            else if(A < abs(B)) cout << "<" << "\n";
            else cout << "=" << "\n";            
        }else{
            cout << ">" << "\n";
        }
    }else{
        if(C % 2 == 0){
            if(abs(A) > abs(B)) cout << ">" << "\n";
            else if(abs(A) < abs(B)) cout << "<" << "\n";
            else cout << "=" << "\n";
        }else{
            if(abs(A) > abs(B)) cout << "<" << "\n";
            else if(abs(A) < abs(B)) cout << ">" << "\n";
            else cout << "=" << "\n";
        }
    }
}