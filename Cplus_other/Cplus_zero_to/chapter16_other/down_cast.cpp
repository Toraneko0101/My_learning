#include <bits/stdc++.h>
using namespace std;

class Base{
public:
    virtual ~Base(){}
};

class Sub1 : public Base{};


int main(){

    //downcast
    Sub1 *sub1 = dynamic_cast<Sub1*>(new Base());

}