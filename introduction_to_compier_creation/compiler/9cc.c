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

//入力文字列
char *user_input;

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
//エラー箇所の報告
void error_at(char *loc, char *fmt, ...){
  va_list ap;
  va_start(ap, fmt);

  int pos = loc - user_input;
  fprintf(stderr, "%s\n", user_input);
  fprintf(stderr, "%*s", pos, " ");//pos個の空白
  fprintf(stderr, "^ ");
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
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
// それ以外の場合はエラーを報告する(expectedが-確定になる)
bool expect(char op){
  if (token->kind != TK_RESERVED || token->str[0] != op){
    error_at(token->str, "expected '%c'", op);
  }
  //次のtokenへ
  token = token->next;
}

// 次のトークンが数値の場合、トークンを1つ進めて数値を返す
// それ以外の場合はエラーを報告する
int expect_number(){
  if (token->kind != TK_NUM){
    error_at(token->str, "expected a number");
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
  Token *tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->str = str;
  cur->next = tok;
  return tok;
}

// 入力文字列pをトークナイズし、それを返す
Token *tokenize(){
  char *p = user_input;
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

    error_at(p, "expected a number");
  }
  //末尾の場合、記号で終わることはないのでpはstrtolで範囲外を示しているはずだ
  new_token(TK_EOF, cur, p);
  //連結リストの最初の要素アドレスを返す
  return head.next;
}

int main(int argc, char **argv){
  if(argc != 2){
    //引数の個数
    error("%s: invalid number of arguments", argv[0]);
    return 1;
  }
  //トークナイズする
  user_input = argv[1];
  token = tokenize();

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