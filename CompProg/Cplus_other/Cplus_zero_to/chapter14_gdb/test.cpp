#include <iostream>
int main(){
    int i{};
    while (i != 1000){
        ++i;
        std::cout << i;
    }
}
// (gdb) break 6 if i == 500