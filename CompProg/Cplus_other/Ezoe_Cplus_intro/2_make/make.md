```
・複雑な依存関係を解決するためにMakeを使う
<Makefileには変数が書ける>
var = foobar
target : $(var)

<自動変数>
・target : $@
・1つ目の要件 : $<
・全ての要件: $^

<PHONY>
・targetと同じ名前が存在する時用
⇒通常は、すでにupdate済み扱いされてしまう
.PHONY: target名とすることで、ターゲットと同じファイル名の存在有無にかかわらず実行が可能。
```