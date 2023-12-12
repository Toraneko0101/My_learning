/**
 * ストリームに対する設定は、それ以後すべての処理に適用される
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    //true,falseの表示
    cout << boolalpha << true << "\n";
    cout << noboolalpha << false << "\n";

    //浮動小数点数の表示形式
    const double x = 100.0 / 3.0;
    cout << x << "\n";
    /**
     * defaultではこれは、デフォルト表記になっている
     * ⇒値を指数表記した際に、指数部分が-5以下か、表示精度6以上である場合は指数表記
     * ⇒それ以外は通常表記
     * ⇒小数部分の末尾0は削除する
    */
    cout << 0.0000007 << "\n"; //指数
    cout << 0.000006 << "\n"; //指数
    cout << 0.00005 << "\n"; //指数
    cout << 0.0004 << "\n"; //通常
    cout << 500000.0 << "\n"; //通常
    cout << 6000000.0 << "\n"; //指数部分が6以上なので指数
    cout << 70000000.0 << "\n"; //指数

    //浮動小数点数の表示精度を変更(デフォルト表記の場合、表示精度0は1とみなされるらしい)
    cout << std::setprecision(10) << x << endl;
    
    //固定小数点表記に設定
    //std::fixed
    //整数部分はそのまま表示し、小数点以下は表示精度まで(末尾0は削除しない)
    cout << std::fixed << 70000000.0 << "\n";

    //常に指数表記での表示に変更。小数部分は表示精度まで(末尾0は削除しない)
    cout << std::setprecision(6);
    cout << std::scientific << 123.12 << "\n";

    //デフォルト表記に戻す
    cout << std::defaultfloat << x << endl;
    
    //新しいストリームオブジェクトを作れば制度の設定はデフォルトに戻す
    cout << std::setprecision(10);
    std::stringstream ss;
    ss  << 1.31456789661;
    cout << ss.str() << endl; //1.31457

}