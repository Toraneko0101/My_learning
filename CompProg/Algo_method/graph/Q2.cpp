#include <bits/stdc++.h>
using namespace std;

int main(){
    int N, M;
    cin >> N >> M;
    vector<vector<int>> graph(N);
    for (int i=0; i<M; i++){
        int A,B;
        cin >> A >> B;
        graph[A].push_back(B);
    }

    for(int i=0; i<N; i++){
        sort(graph[i].begin(), graph[i].end());

        for(int j=0; j<graph[i].size(); j++){
            if(j>=1) cout << " ";
            cout << graph[i][j];
        }
        cout << endl;
    }
}