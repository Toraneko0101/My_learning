- error
```
・gccのエラーは以下のformat
    ソースファイル名:行番号:列番号:メッセージの種類:メッセージの内容
・コンパイラが1つ後の行を指定したりするのは、;がない以上続けて見えているから

例)
main.cpp:4:5: error: expected `,` or `;` before `auto`
    auto y = x + 1 ;
    ^~~~

・プログラムがエラーを通知する仕組み
⇒main関数の戻り値。なにも返さない場合return 0
⇒main関数が0 or EXIT_SUCCESSを返すと成功通知扱いになる
⇒0以外 or EXIT_FAILUREを返すとエラー通知が可能

・文法エラーの場合、コンパイラは人間が誤りそうなパターンをヒューリスティックに指摘するので、必ずしも一致しないことがある

・意味エラーの場合、ソースファイルは文法的に正しい。

・gccのバージョンなどが原因で、コンパイラ関係のエラーが出ることもある
```
- 警告メッセージ
```
・疑わしいコードに対してGCCはエラーを出す

例)
- Wunused-variable
    変数を宣言したにもかかわらず使っていない箇所がある
- Wparentheses
    真偽値として使われる代入は括弧で囲むべき
```