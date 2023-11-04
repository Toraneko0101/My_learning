# Step2: 加減算のできるコンパイラ
- 目標
```
・コンパイルするときに計算して結果を埋め込むのはらしくない
・加減算を実行時に行うアセンブリを出力する

add
    加算
sub
    減算
```

- アセンブリの例
```
.intel_syntax noprefix
.globl main

main:
    mov rax, 5
    add rax, 20
    sub rax, 4
    ret
```

- 自然言語として考えると?
```
・最初に数字が一つある
・そのあとに0個以上の項が続く
・項は+または-の後に数字が来ているものを指す
```
- Cのコードに落とす
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "引数の個数が正しくありません\n");
    return 1;
  }
  //コマンドライン引数は、通常ダブルクォートで囲まれた文字列として渡される
  char *p = argv[1];
  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");
  //strtol(s:変換文字列,endp:終了位置,base:基数)
  //数値として解釈できない文字があるとそこまでの文字列を返し、解釈できないアドレスをendpに代入
  //今回の場合、endpは&pで,pは文字列なので、文字列の先頭位置が更新される
  //pはポインタだが、pのアドレスを変更する必要があるので&p
  //5+20-4なら、5を読み込んだ後、ポインタは+を指すようになる
  //strtol(const char *s, char **endp, int base);
  // &p = **char
  // p = *char
  // endpはポインタを格納するためのポインタでなければならない
  // endpポインタが指し示す場所に、未処理の文字列の新しい位置を設定するのだ

  printf("  mov rax, %ld\n", strtol(p, &p, 10));
  while (*p){
    if(*p == '+'){
      p++;
      printf("  add rax, %ld\n", strtol(p, &p, 10));
      continue;
    }

    if(*p == '-'){
      p++;
      printf("  sub rax, %ld\n", strtol(p, &p, 10));
      continue;
    }

    fprintf(stderr, "予期しない文字です: '%c'\n", *p);
    return 1;
  }

  printf("  ret\n");
  return 0;
}
```

- コメントを消したもの
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "引数の個数が正しくありません\n");
    return 1;
  }
  char *p = argv[1];
  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");
  printf("  mov rax, %ld\n", strtol(p, &p, 10));
  while (*p){
    if(*p == '+'){
      p++;
      printf("  add rax, %ld\n", strtol(p, &p, 10));
      continue;
    }

    if(*p == '-'){
      p++;
      printf("  sub rax, %ld\n", strtol(p, &p, 10));
      continue;
    }

    fprintf(stderr, "予期しない文字です: '%c'\n", *p);
    return 1;
  }

  printf("  ret\n");
  return 0;
}

```

- 手順
```
$ make
$ ./9cc "20+11-7"
$ make test
tmpは最後のassert文の出力が反映される

```