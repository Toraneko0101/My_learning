//2進数 -> 10進数
int two_to_ten(std::string two, int keta){
    int num = two.back() - '0';
    if(size(two) == 1) return num * keta;
    else{
        two.pop_back();
        num *= keta;
        keta *= 2;
        return num + two_to_ten(two, keta);
    }
}

int main(){
    std::string two = "10100110";
    int keta = 1;
    std::cout << two_to_ten(two, keta) << "\n"; 
    
    //そんなことしなくても行ける
    //10進数 -> 2進数
    long long n;
    std::cin >> n;
    std::bitset<10> bs(n);
    std::cout << bs << "\n";

    //C++20ならformatでより簡単(0-padding)
    std::string s = std::format("{:0>10b}", n);
    std::cout << s << "\n";

    //2進数 -> 10進数
    std::bitset<10> bits(two);
    int decimal = (int)bits.to_ulong();
    std::cout << decimal << "\n";
}