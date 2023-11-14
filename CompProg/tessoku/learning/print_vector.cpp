#include <bits/stdc++.h>
//#include <gtest/gtest.h>
using namespace std;

int main(){
    vector<string> v = {"a", "b", "c", "d"};
    copy(v.begin(), v.end(), ostream_iterator<string>(cout, ","));
    cout << endl;
}