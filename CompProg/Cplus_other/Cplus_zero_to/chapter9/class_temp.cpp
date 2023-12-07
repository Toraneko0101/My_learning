/**
 * クラスに対するtemplate
*/

#include <bits/stdc++.h>
using namespace std;

//定数も例示した
template <typename T, typename U, int N>
class Rectangle{
public:
    Rectangle(T height, U width) : 
        height_(height),
        width_(width){}
    //decltype(std::declval<T>() * std::declval<U>())
    auto Area() const -> decltype(auto){
        cout << N << endl;
        return height_ * width_;
    }

private:
    const T height_;
    const U width_;
};

int main(){
    Rectangle<int, double, 10> r1(9,20.2);
    cout << r1.Area() << endl;
}