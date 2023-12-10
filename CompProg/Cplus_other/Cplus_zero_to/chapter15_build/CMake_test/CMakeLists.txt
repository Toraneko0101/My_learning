#最低限のCMakeのversion
cmake_minimum_required(VERSION 3.10)

#プロジェクトの名前
project(CMake_test)

#実行可能ファイルの作成
add_executable(my_executable src/main.cpp)

#プロジェクト名がCMake_testで
#srcディレクトリ内のmain.cppを含む実行可能ファイルを
#my_executableという名前で生成する