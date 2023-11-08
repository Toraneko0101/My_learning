# スタックマシン
```
・構文木をアセンブリに変換する方法について学ぶ
```
- なぜ加減算と同じ方法でアセンブリに変換できないのか
```
・加減算のできるコンパイラではraxを結果のレジスタとして、中間的な計算結果を1つだけ保持していた。
・しかし、乗除算ができるコンパイラの場合、計算結果を2つ保持する必要がある。たとえば2*3 + 4*5
・このような計算を行うのに適しているのがスタックマシン
```

## スタックマシンの概念
```
スタックマシン
    ・スタックをデータ保存領域として持っているコンピュータ
    ・stackにはpushとpopを行う
    ・LIFO:後入れ先出し。新しい要素ほど先に出す

スタックマシンにおける演算命令
    ・スタックトップ（次に取り出す要素）の要素に作用する
    ・ADDなら2つpopして、加算して結果をstackにpush
    ・ADDはスタックトップの2要素を、加算した1つの要素で置き換える命令
    ・SUB,MUL,DIVも同様
    ・逆ポーランド記法みたい
    ・PUSH命令は引数の要素をスタックトップに積む
    ・POPならスタックトップから要素を1つ取り除き捨てる
```

- 2×3 + 4×5の計算
```asm
PUSH 2
PUSH 3
MUL
PUSH 4
PUSH 5
MUL
ADD
```