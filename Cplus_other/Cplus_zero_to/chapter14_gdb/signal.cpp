#include <vector>
#include <iostream>
int main(){
    std::vector<int> a = {1,2};
    //正常なら(gdb) print aで中身を閲覧可能
    //print a.at(0)で中身も見れる
    //エラーを起こした後だとおかしくなっているように見える。
    std::cout << a.at(10) << std::endl;

}

// Program received signal SIGABRT, Aborted.
// __pthread_kill_implementation (no_tid=0, signo=6, threadid=140737347893056) 
//at ./nptl/pthread_kill.c:44

/**
 * backtraceを調べると、
 * vectorのatで引っかかっていることが分かる
 * 
*/
// (gdb) backtrace
// #0  __pthread_kill_implementation (no_tid=0, signo=6, 
//     threadid=140737347893056) at ./nptl/pthread_kill.c:44
// #1  __pthread_kill_internal (signo=6, 
//     threadid=140737347893056) at ./nptl/pthread_kill.c:78
// #2  __GI___pthread_kill (threadid=140737347893056, 
//     signo=signo@entry=6) at ./nptl/pthread_kill.c:89
// #3  0x00007ffff7b39476 in __GI_raise (sig=sig@entry=6)
//     at ../sysdeps/posix/raise.c:26
// #4  0x00007ffff7b1f7f3 in __GI_abort ()
//     at ./stdlib/abort.c:79
// #5  0x00007ffff7de7f26 in ?? ()
//    from /lib/x86_64-linux-gnu/libstdc++.so.6
// #6  0x00007ffff7df9d9c in ?? ()
//    from /lib/x86_64-linux-gnu/libstdc++.so.6
// #7  0x00007ffff7df9e07 in std::terminate() ()
//    from /lib/x86_64-linux-gnu/libstdc++.so.6
// #8  0x00007ffff7dfa068 in __cxa_throw ()
//    from /lib/x86_64-linux-gnu/libstdc++.so.6
// #9  0x00007ffff7deb2f1 in ?? ()
//    from /lib/x86_64-linux-gnu/libstdc++.so.6
// #10 0x0000555555555bdf in std::vector<int, std::allocator<int> >::_M_range_check (this=0x7fffffffd960, __n=10)
//     at /usr/include/c++/13/bits/stl_vector.h:1155
// #11 0x0000555555555a61 in std::vector<int, std::allocator<int> >::at (this=0x7fffffffd960, __n=10)
//     at /usr/include/c++/13/bits/stl_vector.h:1177
// #12 0x0000555555555311 in main () at signal.cpp:5

/**
 * エラーを起こしたときにデバッガを起動していなかったら?
 * 
 * コアダンプの場所を確認
 * cat /proc/sys/kernel/core_pattern
 * 
 * coreファイルの名前にはパターンを指定できる
 * ⇒たとえば %eなら実行ファイル名(prefixを除く)
 * /mnt/wslg/dumps/core.signal.132240がコアダンプなら
 * 
 * (gdb) signal /mnt/wslg/dumps/core.signal.132240という風に指定する
 * すると、エラッた時点のプログラムの状態を調べられる
 * 
 * なお、コアダンプが生成されていない場合
 * $ ulimit -c 0となっている可能性がある
 * $ ulimit -c unlimitedとするとコアダンプは無数に生成されるが
 * その分、容量を取るので注意
 * 
*/