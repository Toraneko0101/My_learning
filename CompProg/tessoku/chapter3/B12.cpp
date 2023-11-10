#include <bits/stdc++.h>
using namespace std;

double N;
double x;
string calc(double x){
    double result = x * x * x + x;
    if (result > N) return "too big";
    else if (result < N) return "too small";
    else return "equal"; 
}
int main(){
    cin >> N;
    double Left = 0.0, Right = 100.0, Mid;
    int cnt = 0;
    while(cnt <= 30){
        Mid = (Left + Right) / 2; 
        string judge = calc(Mid);
        if(judge == "too big") Right = Mid;
        else if(judge == "too small") Left = Mid;
        else break; 
        cnt += 1;
    }

    cout << Mid << endl;
    return 0;
}