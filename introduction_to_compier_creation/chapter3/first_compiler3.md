# Step3: トークナイザを導入
```
問題点
    ・現状は文字列に空白があるとエラーになる
    ・空白を読み飛ばすやり方は非推奨
    ・入力を単語に分割する
    ・トークン列の終わりを表す型を用意しておくと簡単になる
    ・トークンはポインタでつないだ連結リストになるようにする
```

- 解説付きC言語
```c
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//トークンの種類(0~3)
typedef enum{
  TK_RESERVED,  //記号
  TK_NUM,       //整数トークン
  TK_EOF,       //入力終了トークン
} TokenKind;

typedef struct Token Token;

//Tokenkindには(0~3)が入る
struct Token {
  TokenKind kind; //トークンの型(enumより)
  Token *next;    //次の入力トークン(次の構造体のアドレス)
  int val;        //kindがTK_NUMの場合、その数値
  char *str;      //トークン文字列
};

//現在着目しているトークン
Token *token;

//エラーを報告するための関数
//可変長引数
void error(char *fmt, ...){
  va_list ap;                 //可変長引数を一つの引数に変換
  va_start(ap, fmt);          //可変長引数リストを初期化(引数リスト,指定した引数以降を引数リストに格納)
  vfprintf(stderr, fmt, ap);  //可変長引数を受け取り、第1引数に第2引数で指定したfmtで、errorメッセージを出力
  fprintf(stderr, "\n");      //第1引数に、出力
  exit(1);                    //終了ステータス
}

// 次のトークンが期待している記号の時はトークンを1つ進めて真
// それ以外の場合は偽を返す
bool consume(char op){
  if (token->kind != TK_RESERVED || token->str[0] != op){
    return false;
  }
  //次のtokenへ
  token = token->next;
  return true;
}

// 次のトークンが期待している記号の時はトークンを1つ進めて真
// それ以外の場合はエラーを報告する
bool expect(char op){
  if (token->kind != TK_RESERVED || token->str[0] != op){
    error("'%c'ではありません", op);
  }
  //次のtokenへ
  token = token->next;
}

// 次のトークンが数値の場合、トークンを1つ進めて数値を返す
// それ以外の場合はエラーを報告する
int expect_number(){
  if (token->kind != TK_NUM){
    error("数ではありません");
  }
  //次のtokenへ
  int val = token->val;
  token = token->next;
  return val;
}

//tokenがEOFなら真を返す
bool at_eof(){
  return token->kind == TK_EOF;
}

// 新しいトークンを作成してcurにつなげる
// cur.next 
// 構造体の情報はcallocでメモリを確保しているので格納され続ける
Token *new_token(TokenKind kind, Token *cur, char *str){
  //malloc関数で確保して、領域を0で初期化
  //mallocと異なり、要素数と要素サイズを指定可能。
  Token *tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->str = str;
  cur->next = tok;
  return tok;
}

// 入力文字列pをトークナイズし、それを返す
Token *tokenize(char *p){
  Token head; //トークンのリストの先頭を指す。head.nextで先頭
  head.next = NULL;
  //一回目のloopではculがheadのアドレスを指しているので
  //head.nextは連結リストの先頭を指す。それ以降は
  //curはheadのアドレスを指していないので変更されない
  Token *cur = &head; 
  //空白文字のスキップ
  while (*p){
    if (isspace(*p)){
      p++;
      continue;
    }
    if (*p == '+' || *p == '-'){
      //ポストインクリメントなので、式で使用された後に増加させる
      //一回目 cur = head 
      //       cur.next = first_tok
      //二回目 cur = first_tok 
      //       cur.next = another_tok
      //以上のように連結されていく
      cur = new_token(TK_RESERVED, cur, p++);//トークン作成
      continue;
    }

    if(isdigit(*p)){
      cur = new_token(TK_NUM, cur, p);
      cur -> val = strtol(p, &p, 10); //数値を返す
      continue;
    }

    error("トークナイズできません");
  }
  //末尾の場合、記号で終わることはないのでpはstrtolで範囲外を示しているはずだ
  new_token(TK_EOF, cur, p);
  //連結リストの最初の要素アドレスを返す
  return head.next;
}

int main(int argc, char **argv){
  if(argc != 2){
    error("引数の個数が正しくありません");
    return 1;
  }
  //トークナイズする
  token = tokenize(argv[1]);

  //アセンブリの前半部分を出力
  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");

  //式の最初は数である必要があるのでチェック
  //最初のmov命令を出力
  printf("  mov rax, %d\n", expect_number());

  // -<num> +<num>という並びを消化する
  while (!at_eof()){
    if (consume('+')){
      printf("  add rax, %d\n", expect_number());
      continue;
    }
    //もしマイナスでもなければerror
    expect('-');
    printf("  sub rax, %d\n", expect_number());
  }

  printf("  ret\n");
  return 0;
}
```