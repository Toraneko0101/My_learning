#include <iostream>
using namespace std;

int main(){
    int val{};
    val = 10;
    cout << val << endl;
    return 0;
}

/**
 * buildの手順
 * 1. cmakeがinstallされているか確かめる
 * 2. プロジェクトのディレクトリに移動
 * 3. ビルドディレクトリを作成
 * 4. ビルドディレクトリに移動
 * 5. cmakeでビルドfileを作成
 * cmake .. (親に対してってことか)
 * 6. Makeを使ってビルド
 * make
 * ⇒build内に生成されたことが確認された
 * ⇒CMakeLists.txtを変更することで、
 * 異なるプラットフォームやビルドツールによるビルドが可能になる
 * ⇒ついでに、.gitignoreにbuildを指定した
 * 
 * buildディレクトリを作るのは
 * ソースコードとビルド結果を分離するため
 * ⇒アウトオブソースビルド
 * ⇒何もしないと現在のディレクトリのサブディレクトリにビルド結果が出力されるので
 * ⇒cmake ..のサブディレクトリはbuildディレクトリ
*/

// $ tree -L 2
// .
// ├── CMakeLists.txt
// ├── build
// │   ├── CMakeCache.txt
// │   ├── CMakeFiles
// │   ├── Makefile
// │   ├── cmake_install.cmake
// │   └── my_executable
// └── src
//     └── main.cpp

/**
 * 3.13以上であれば3番以下の手順を、次のように可能
 * //ソース(プロジェクトの中身)とビルドを指定
 * //該当のディレクトリがなければ作成してくれる(build)
 * 3. cmake -S . -B build
 * 4. cmake --build build
 * ⇒makeがMakefileがあるディレクトリで実行されることを前提としているのに対し
 * ⇒cmake --build buildは可能。
 * ⇒現在のディレクトリがbuild/なら
 * =>cmake --build .でいけるはず
*/