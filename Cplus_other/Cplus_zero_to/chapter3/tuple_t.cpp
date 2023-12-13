#include <bits/stdc++.h>
using namespace std;

int main(){
    tuple<string, int, int> person {"Bob", 20, 12};
    tuple<string, int> area = make_tuple("Neko",12);
    cout << get<0>(person) << "\n";
    //構造体束縛(std::tie)を利用してもいい
    //std::tie(a,std::ignore, c) = person;
    auto [a,b,c] = person;

    pair<string, int> My_pair = make_pair("Neko", 13);
    cout << My_pair.first << My_pair.second << "\n";
    

}