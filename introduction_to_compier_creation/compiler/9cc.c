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

//エラー箇所の報告(*locは現在のpointer)
void error_at(char *loc, char *fmt, ...){
  va_list ap;
  va_start(ap, fmt);                    //apがさす位置はfmtとなる

  int pos = loc - user_input;           //つまり、posには何文字進んだかが入る
  fprintf(stderr, "%s\n", user_input);
  fprintf(stderr, "%*s", pos, "");      //pos個の空白(*は、第二引数の文字列分、第3引数を表示。足りないなら空白パディング)
  fprintf(stderr, "^ ");
  vfprintf(stderr, fmt, ap);            //可変個数の引数を指定した書式(第二引数)に従って、第1引数に返す
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
  Token head;
  head.next = NULL;
  Token *cur = &head; 
  //空白文字のスキップ
  while (*p){
    if (isspace(*p)){
      p++;
      continue;
    }
    //Punctuator
    if (strchr("+-*/()", *p)){
      cur = new_token(TK_RESERVED, cur, p++);//トークン作成
      continue;
    }

    if(isdigit(*p)){
      cur = new_token(TK_NUM, cur, p);
      cur -> val = strtol(p, &p, 10); //pは数値の次を指す
      continue;
    }

    error_at(p, "invalid token");
  }
  new_token(TK_EOF, cur, p);
  return head.next;
}

//Parser
typedef enum{
  ND_ADD,
  ND_SUB,
  ND_MUL,
  ND_DIV,
  ND_NUM, //Int
} NodeKind;

typedef struct Node Node;

struct Node{
  NodeKind kind;
  Node *lhs;
  Node *rhs;
  int val;
};

Node *new_node(NodeKind kind){
  Node *node = calloc(1, sizeof(Node));
  node->kind = kind;
  return node;
}

Node *new_binary(NodeKind kind, Node *lhs, Node *rhs){
  Node *node = new_node(kind);
  node->lhs = lhs;
  node->rhs = rhs;
  return node;
}

Node *new_num(int val){
  Node *node = new_node(ND_NUM);
  node->val = val;
  return node;
}

Node *expr();
Node *mul();
Node *primary();

Node *expr(){
  Node *node = mul();
  //値を返す(+,-が来なくなったら終わり)
  for(;;){
    if(consume('+'))
      node = new_binary(ND_ADD, node, mul());
    else if(consume('-'))
      node = new_binary(ND_SUB, node, mul());
    else
      return node;
  }
}

Node *mul(){
  Node *node = primary();

  for(;;)
    if(consume('*'))
      node = new_binary(ND_MUL, node, primary());
    else if(consume('/'))
      node = new_binary(ND_DIV, node, primary());
    else
      return node;
}

Node *primary(){
  //consumeで記号を予測する
  if(consume('(')){
    Node *node = expr();
    expect(')');
    return node;
  }

  return new_num(expect_number());
}

void gen(Node *node){
  if(node->kind == ND_NUM){
    printf("  push %d\n", node->val);
    return;
  }
  //左優先で探索(式の形にならこっちに来る)
  gen(node->lhs);
  gen(node->rhs);

  printf("  pop rdi\n");
  printf("  pop rax\n");

  switch (node->kind){
    case ND_ADD:
      printf("  add rax, rdi\n");
      break;
    case ND_SUB:
      printf("  sub rax, rdi\n");
      break;
    case ND_MUL:
      printf("  imul rax, rdi\n");
      break;
    case ND_DIV:
      printf("  cqo\n");
      printf("  idiv rdi\n");
      break;
  }

  printf("  push rax\n");
}

int main(int argc, char **argv){
  if(argc != 2){
    //引数の個数
    error_at("%s: invalid number of arguments", argv[0]);
    return 1;
  }
  //記号と数値を分離
  user_input = argv[1];
  //Token同士をつなげる
  token = tokenize();
  //Nodeを生成しつなげる(これはlhsとrhsを持つ:ルートのNodeが返る)
  Node *node = expr();

  //アセンブリの前半部分を出力
  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");

  //抽象構文木を下りながらコード生成
  gen(node);


  printf("  pop rax\n"); //戻り値をraxに
  printf("  ret\n");
  return 0;
}