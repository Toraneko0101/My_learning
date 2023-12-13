/**
 * 単体テストをするためには
 * 部品ごとに分解されたプログラムであることが望ましい
 * 
 * 機能が関数やクラス単位で明確に分離されていれば
 * テストは行いやすく、また可読性もあがる
 * 
 * 
*/


/**
 * GoogleTest(Ubuntuの導入)
 * 
 * 1. UbuntuのUpdate
 * 2. Cmakeのinstall(GoogleTestのbuild用)
 * 3. GoogleTestのClone(home/program_fileに展開した)
 * $ git clone https://github.com/google/googletest.git
 * 
 * 4. GoogleTestのinstall
 * $ cd googletest
 * $ mkdir build
 * $ cd build
 * //build
 * $ cmake ..
 * $ make
 * //install
 * $ sudo make install
 * 
 * 5. 結果
 * $ cd /usr/local/include
 * $ ls
 * gmock gtest
 * 
*/

//googletest用のinclude
//defaultだけだとなみなみ引かれるので、
//.vscode/c_cpp_properties.jsonにinclude_pathを追加する事
#include <gtest/gtest.h>

int add(int a, int b){
    return a+b;
}

TEST(TestCase, add){
    EXPECT_EQ(10, add(7, 3));
}

/**
 * test実行時のコマンド
 * g++ -std=c++20 unittest.cpp 
 * -lgtest_main -lgtest -lpthread -o test
*/

/**
 * Running main() from /home/user/program_file/googletest/googletest/src/gtest_main.cc
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from TestCase
[ RUN      ] TestCase.add
[       OK ] TestCase.add (0 ms)
[----------] 1 test from TestCase (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
*/