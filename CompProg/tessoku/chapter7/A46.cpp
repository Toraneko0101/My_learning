#include <bits/stdc++.h>
using namespace std;

int N;
double X[159], Y[159];
bool visited[159];

double getDistance(double a, double b){
    return pow(X[a]-X[b]);
}
int main(){
    cin >> N;
    for(int i=1; i<=N; i++) cin >> X[i] >> Y[i];
}