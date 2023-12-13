#include <bits/stdc++.h>
using namespace std;

//型変換を明示的に行って、explicit指定された引数1つのもので
//変換コンストラクタと同等の動作を行う
//変換コンストラクタ、引数の型をクラスの型に変換なので
class Square{
public:
    explicit Square(int size) : size_(size){}

private:
    int size_;
};

int main(){
    /**
     * static_cast:明示的な型変換を行う
     * 
    */
    double dx = 3.14;
    int x = static_cast<int>(dx);
    cout << x << "\n";

    enum class Day{
        Sun,Mon,Tue,Wed,Thu,Fri,Sat
    };

    //列挙と数値型の相互変換
    Day day1 = static_cast<Day>(1);
    int day2 = static_cast<int>(Day::Tue);

    //疑似、変換コンストラクタ
    Square s = static_cast<Square>(10);

    /**
     * 他のキャストについて
     * Cライクなキャスト
     * ⇒記法が明解ではなく、どのキャストが選ばれるかもわからないので却下
     * 
     * dynamic_cast
     * ・ダウンキャストをする際に用いる
     * ・アップキャストに使う時は、static_castと同じ意味になる
     * ・クラスに仮想関数が少なくとも1つ必要
     * ・基底⇒派生への参照やポインタへの型変換
     * ・実行時にキャストの成否を判断する
     * 
     * const_cast
     *  const修飾子を外すときに用いるキャスト
     *  ポインタや参照、データメンバへのポインタのconst属性を変更するために使用する
     *  const修飾を付加する際はstatic_castと同一
     * 
     * reinterpret_cast
     *  値は変えず、型情報の変換を行う
     *  使わない方が望ましい
     *  バイナリ単位で何かを変えたいときなどに利用?
    */


    //const_cast
    const int i0 = 5;
    //constであるi0の参照をconst_castで外す
    int& i1 = const_cast<int&>(i0);
    i1 = 11;
    cout << i1 << endl;
    cout << i0 << endl; //変更されない

    //通例、constであるものをconstでない参照では参照できない
    // const int i2 = 5;
    // int &i3 = i2;

    //reinterpret_cast
    long l = 5000;
    int *p = reinterpret_cast<int *>(l);
    cout << p << endl;
}