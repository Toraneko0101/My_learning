/**
 * 書き出し
 * std::ofstream
 * 通常上書き
 * 
*/

#include <bits/stdc++.h>
using namespace std;

int main(){
    //上書き
    ofstream file("output.txt");
    //追記
    //ofstream file("output.txt", std::ios::app);
    vector<string> fruits = {
        "apple",
        "banana",
        "calamansi",
        "dragon fruits",
        "elephant apple",
        "feijoa",
        "grape",
        "Hassaku",
        "icacina",
        "jujuba",
        "kiwi",
        "lemon",
        "melon",
        "nectarine",
        "orange",
        "peach",
        "quince",
        "raspberry",
        "strawberry",
        "tangor",
        "ugli fruit",
        "valencia orange",
        "watermelon",
        "ximenia",
        "yuzu",
        "zabergau reinette"
    };

    for(const auto fruit: fruits){
        file << fruit[0] << " : " << fruit << endl; //書き出し(\nではなくflushする)
    }
    return 0;
}