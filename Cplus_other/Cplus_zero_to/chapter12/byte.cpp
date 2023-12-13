#include <bits/stdc++.h>
using namespace std;
/**
 * 1byte
 * char, signed char, unsigned char
 * 以前はbitを扱う際、符号なしのunsigned charを用いていたが
 * 今日ではstd::byte(C++17 ~)を使う
*/

int main(){
    //2種の初期化方法
    //popcountなどはunsigned intに対する操作だからこれはちょっと違うか
    std::byte a{0b1010'1010};
    std::byte b = static_cast<std::byte>(0b0000'1111);

    std::byte result = a & b;

    //整数型に変換
    int result_int = static_cast<int>(result);
    cout << result_int << endl;

    //任意の型に変換(static_castではなくこちらを用いるのは、情報損失の際にstd::overflow_error例外を投げるため)
    //static_castだと情報損失が起きても無視する
    //たとえば16桁のbit列を誤って、uini8_tに入れた場合のことを考える
    std::uint8_t result_u8 = std::to_integer<std::uint8_t>(result);
    assert(result_u8 == 0b0000'1010);

    cout << CHAR_BIT << "\n";
    cout << SCHAR_MIN << "\n"; //値の範囲の最小(-128)
}

/**
 * 補足
 * 1byte != 8bits?
 * 
 * 2008年にIEC 80000-13で正式定義される前のコンパイラだと
 * 9bits or 7bitsのものがあったりするらしい
 * 
 * CやC++では
 * char == 1byte
 * charのbit数 CHAR_BIT >= 8bits
 * より、1byte == 9bitsは許容される
 * 
 * 1byte == 8bitsしか想定していないことを明記する例
 * #include <climits>
 * static_assert(CHRR_BIT == 8, "Not support 1byte != 8bits");
 * 
 * たとえばPDP-10は、1byte != 8bits
 * というか昔の4bitCPUなら1byte != 8bitsだろう
*/