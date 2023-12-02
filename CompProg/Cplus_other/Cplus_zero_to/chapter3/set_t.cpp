#include <bits/stdc++.h>
using namespace std;

int main(){
    unordered_set<string> animals = {
        "Nezumi",
        "Usi",
        "Tora"
    };
    animals.insert("Usagi");
    animals.erase("Tora");
}