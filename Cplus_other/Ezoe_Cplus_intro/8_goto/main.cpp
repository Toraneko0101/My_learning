void hello_n(int n){
    int i = 0;
loop:
    if(n < 0) return;
    if(i != n){
        std::cout << "hello\n";
        ++i;
        goto loop;
    }
}

int main(){
    int n; std::cin >> n;
    hello_n(n);
}