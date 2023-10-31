# 正規表現(reqular expression: regex)

# 11.1 正規表現エンジン
```
正規表現エンジン
    ・文字列を理解し、解釈してマッチするテキストを検索するソフトウェア

Linuxにある正規表現エンジン
    基本正規表現
        Basic Regular Expressionエンジン(BRE)
    拡張正規表現
        Extended Regular Expressionエンジン(ERE)
    
・grepの場合、-EでEREを理解
・sedやawkなどは両方解釈可能
・Linux向けのC言語ランタイムライブラリであれ宇GNU C LibraryでBREとEREの機能が提供されている
```

# 11.2 BREパターンの定義
```
$ echo "Welcome to shell scripting" | sed -n '/shell/p'
$ echo "Welcome to shell scripting" | awk '/shell/{print $0 }'

$0は行ごと表示
```

## 11.2.1 アンカー文字
```
- 先頭にマッチ
$ echo "Welcome to shell scripting" | awk '
/^Welcome/{
    print $0
}'

- 末尾にマッチ
$ echo "Welcome to shell scripting" | awk '
/ting$/{
    print $0
}'

・awkで^を文字として検索したい場合は、\でエスケープする
・sedの場合はエスケープする必要はない

- 空行にマッチ(!は否定なので)
$ awk '!/^$/{print $0 }' myfile
```

## 補足
```
・正規表現がマッチしているか調べるときは~を使うみたいだ。
・マッチしない場合に真にしたいなら!~

$ echo "neko" | awk '{
    if($0 !~ /^n/){
        print "nekodayo"
    }
}'


```

## 11.2.2 ドット文字
```
$ awk '{
    if($0 ~ /.sh/){
        print $0
    }
}' test2.txt
```

## 11.2.3 文字クラス
```
特定のいくつかの文字のみにマッチさせる

$ awk '{
    if($0 ~ /[mbr]ash/){
        print $0
    }
}' test3.txt

[Ww]
    大文字と小文字にマッチ

[^br]
    b,r以外の文字にマッチ
$ awk '{
    if($0 ~ /[^br]ash/){
        print $0
    }
}' test3.txt

```

## 11.2.4 一連の文字
```
[a-d]
    a~dまでの文字にマッチ

[0-9]
    数字にマッチ

[d-hm-z]
    d~hとm~zにマッチ
[a-zA-Z]
    全てのアルファベットにマッチ

$ awk '{
    if($0 ~ /[a-m]ash/){
        print $0
    }
}' test3.txt
```

## 11.2.5 特殊文字クラス
```
よく使われる文字セットにマッチさせるためのもの
[[:alpha:]]
    任意のアルファベットにマッチ
[[:upper:]]
    大文字にマッチ
[[:lower:]]
    小文字にマッチ
[[:alnum:]]
    任意のアルファベットと0~9にマッチ
[[:blank:]]
    スペースとタブだけにマッチ
[[:space:]]
    任意の空白文字にマッチ
[[:digit:]]
    0~9にマッチ
[[:print:]]
    任意の印字可能文字にマッチ
[[:punct:]]
    任意の句読文字にマッチ

$ awk '{
    if($0 ~ /[[:alpha:]]ash/){
        print $0
    }
}' test3.txt
```

## 11.2.6 アスタリスク
```
*
    0個以上存在するものにマッチ

$ echo "Checking colors" | awk '{
    if ($0 ~ /colou*rs/){
        print $0
    }
}'

.*
    任意の文字を0個以上繰り返す

$ awk '{
    if ($0 ~ /this.*/){
        print $0
    }
}' test4.txt

$ echo "toot" | awk '/t[aeor]*t/{print $0}'
```

# 11.3 EREパターンの定義
```
・疑問符
・プラス記号
・波括弧
・パイプ文字
・正規表現のグループ化
```

## 11.3.1 疑問符
```
前の文字が0or1
長い文字列のどこかが引っかかれば通過する

$ echo "tt" | awk '{
    if ($0 ~ /t[oa]?t/){
        print $0
    }
}'
```

## 11.3.2 プラス記号
```
前の文字が1個以上
$ echo "tot" | awk '{
    if ($0 ~ /t[oa]+t/){
        print $0
    }
}'
```

## 11.3.3 波括弧
```
存在する数の範囲を定義する
$ echo "taot" | awk '{
    if ($0 ~ /t[oa]{1,2}t/){
        print $0
    }
}'
```

## 11.3.4 パイプ文字
```
・論理ORのようなもの
・パイプ文字と単語の間にはスペースを含まないこと
-e:
    echoでエスケープ文字を解釈するやつ

$ echo -e "shell script\nbash script\nsh script" | awk '{
    if($0 ~ /bash|shell/){
        print $0
    }
}'
```

## 11.3.5 正規表現のグループ化
```
グループ化を行った例
(bash scripting){2}
    bash scriptingという文字列が2個存在するものを探す

$ echo "I'm nyanko nekoneko" | awk '{
    if ($0 ~ /(neko){2,}/){
        print $0
    }
}'
```

# 11.4 grepの使用
```
grepはEREのほかに、Perl互換正規表現をサポートしている

Perl互換正規表現(PCRE)
    ・\d, \s, \wなどを利用可能
    ・\D, \S, \Wなどもいけるはず
    ・GNU grepの場合-pでPCREを使用可能

grep
    ・デフォルトではBRE
    ・-EでERE

grep: 特定パターンの検索
sed: テキストの編集、置換、変換
awk: データの抽出、加工って感じか?

ファイル本体の編集ならsedを使った方がよさそうだな。置換ならgsubでできたはず。でもsedの方が楽そうだし
```
- BRE
```
$ grep ".sh" test2.txt
```
- ERE
```
$ grep -E "(to){1}" test2.txt
```

# 11.5 まとめ
- 全文検索(catでいいような気もする)
```
$ grep "^.*$" test2.txt
$ sed -n '/^.*$/p' test2.txt
$ awk '/.*/{print $0}' test2.txt
```

- 置換
```
sed "/^Wel/c I'm cat" test2.txt
```

- 挿入
```
sed "/^Wel/i Neko is beautiful" test2.txt
```

- 削除
```
sed "/^Wel/d" test2.txt
```

- 特定の行を削除(awk)
```
FNRを使えばいいと思う
```

# 11.6 練習問題
- 11.1
```
0行
```
- 11-2
```
2行
```
- 11-3
```
全行(?は0回を許容するので)
```
- 11-4
```
sedの場合、EREの機能を使うには-rが必要
```