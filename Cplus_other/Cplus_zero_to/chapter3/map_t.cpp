#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main(){
    unordered_map<string, int> persons{
        {"Alice", 18},
        {"Bob", 20},
        {"Charry", 19}
    };

    if(!persons.contains("Alice")){
        persons.insert({"Alice", 10});//insertを使って既存の要素を更新しようとするとエラーになる
        //persons["Alice"] = 10;
    }else{
        cout << persons["Alice"] << "\n";
        persons.erase("Alice"); //削除
    }
}