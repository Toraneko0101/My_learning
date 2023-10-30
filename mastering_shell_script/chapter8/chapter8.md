# 8. ストリームエディターの導入
- 概要
```
sed
    stream editor
    ・ファイルを1行ずつ読みこみ、その内容を編集
    ・スクリプト内でsedを使う場合、人間との対話は必要ない
```

# 8.1 grepを使ってテキストを表示する
```
grep(global regular expression print):
    ・検索をグローバルに(全ての行に対して)行い、その結果を標準出力する。検索文字列として正規表現を使う
```
## 8.1.1 eth0インタフェース上で受信したデータだけを表示したい
```
1. ip aとすると、ipを確認できる
2. ip a show eth0でもeth0について確認できる
3. grepでも可能
4. ip a | grep "eth0"ならeth0を含む行のみが表示される。
grep -iなら大文字小文字が区別されずに検索される(ignore case)
```
## 8.1.2 ユーザアカウントデータの表示

```
/etc/passwd
    Linuxでのlocalのユーザアカウントデータベース
```
- 自分のデータを含んでいる行のみを表示する
```
$ grep "$USER" /etc/passwd
```

- 新しいユーザアカウントを作成する前に、存在チェックを行う
```
・コマンドラインから実行する際に、$bashとすると、新しいbashが起動され、exitしても新しく開いたシェルだけが閉じる
```
```bash
#!/bin/bash

read -p "Enter a user name: "
if (grep "$REPLY" /etc/passwd > /dev/null) ; then
    echo "The user $REPLY exists"
    exit 1
fi
```
## 8.1.3 システム内のCPU数の表示
```
/proc/cpuinfo
    cpuに関する情報が多く含まれる

$ grep -c name /proc/cpuinfo
    ・CPUまたはコアは名前とともに記されているので、-cでcountする。nameの数を
```
```bash
#!/bin/bash

CPU_CORES=$(grep -c name /proc/cpuinfo)
if (( CPU_CORES < 4 )); then
    echo "A minimus of 4 cores are required"
    exit 1
else
    echo "There are enough cores"
fi
```
- 関数として実装
```bash
#!/bin/bash

check_cores(){
    REQ_CORES=$1
    [ -z $1 ] && REQ_CORES=2
    CPU_CORES=$(grep -c name /proc/cpuinfo)
    if (( CPU_CORES < REQ_CORES )); then
        echo "A minimum of $REQ_CORES cores are required"
        exit 1
    fi
}
```
```bash
#!/bin/bash

source ./cpu_count.sh
type check_cores
check_cores "$1"
```

## 8.1.4 CSVファイルの解析
```
CSVの出力結果を読みやすくする
```
- CSVの色などを変更
```bash
#!/bin/bash
OLDIFS="$IFS"
IFS="," #separator
#1行ごとにsep区切りで、product ,price, quantityに値を代入する
while read product price quantity; do
    #青色 4はitalic 47は背景白
    #
    echo -e "\e[4;34;47m$product \
            ========================\e[0m\n\
            Price : \t $price \n\
            Quantity : \t $quantity \n"
done < "$1"

IFS=$OLDIFS
```
- 絞り込み検索を行う
```
grep -A2
    after2の意味。つまり、マッチする行とその後の2行を表示する

$ ./parsecsv.sh tools.csv | grep -A2 hammer
hammer             ========================
            Price :      10 
            Quantity :   50 
```

# 8.2 sedの基礎を理解する
```
$ sed -n 'p' /etc/passwd
    p: マッチしたパターンを表示
    -n: マッチした行だけを表示(stdoutへの出力を抑制)

$ sed -n '1,3 p' /etc/passwd
    headコマンドと同様

$ sed -n '/^root/ p' /etc/passwd
    grepコマンドの再現
    /^が先頭ってのは習ったよね
```

## 8.2.1 置換コマンド
- flagとは
```
$ sed s/pattern/replace/flag

p:
    flagの1つ
    置換が行われた場合に、置換後の文字列を出力
g:
    全ての出現箇所をグローバルに置換
w <file_name>
    結果をファイルに書き出す

※pは置換を行わず、単に画面に表示するだけなので安全
```
- 置換の例
```
$ sed -n '/^toraneko/ s/bash/sh/p' /etc/passwd

-n:
    stdoutへの出力を抑制
'/^toraneko/: 
    toranekoで始まる行を検索
s/bash/sh/p: 
    bashをshで置き換えpで画面に表示
/etc/passwd: 
    対象のファイル

※問題点 
    bashがほかの場所に含まれている可能性もある
    Tabash -> Tash

※解決策?
    /bin/bash -> /bin/shに置換する
    その際、/を\でエスケープする
    $ sed -n '/^toraneko/ s/\/bin\/bash/\/bin\/sh/p' /etc/passwd

※読みにくい?
    ・最初に使う区切り文字によって、区切り文字は定義される
    ・区切り文字は任意の文字として扱える

改善案(@を区切り文字とした)    
    $ sed -n '/^toraneko/ s@/bin/bash@/bin/sh@p' /etc/passwd
全て置換する場合、gコマンドをpの後に追加
    $ sed -n '/^toraneko/ s@/bin/bash@/bin/sh@pg' /etc/passwd
```

## 8.2.2 グローバル置換

- 各行で最初にヒットしたものだけ
```
$ sed 's/sed/Linux sed/' test.txt
```
- replaceall
```
$ sed 's/sed/Linux sed/g' test.txt
```
- w_flagを使って、変更をファイルに書き出す(ファイルの指定が必要)
```
$ sed 's/sed/Linux sed/gw output.txt' test.txt
```
- 指定した順番の出現箇所だけを書き換えたいときは以下の様にする。(各行で2番目にマッチしたものだけを書き換える)
```
$ sed 's/sed/Linux sed/2' test.txt
```

## 8.2.3 置換の限定
```
特定の行や特定の範囲の行だけに編集を限定したい場合
```
```
- 3~5行
$ sed '3,5s/old text/new text/' myfile
- 2~end
$ sed '2,$s/old text/new text/' myfile
```

## 8.2.4 ファイルの編集
```
・wは編集結果をファイルに書き出す
・この場合、変更行のみが書き込まれる。普通に出力を別ファイルに移したかったら、リダイレクトすればいいんじゃね？
・-iオプションはファイルそのものを編集可能
・ファイルを編集する場合はnオプションやpコマンドは必要ない
・ファイルを変更するので、-iオプションの後で文字列を追加して、バックアップファイルを作成しておく
$ sed -i.bak '1s/sed/Neko/g' test.txt

・test.txt.bakが作成されるので、問題があればcpで復元する
```

# 8.3 sedのその他のコマンド

```
テキストの挿入、変更、削除、変換もsedで可能
```

## 8.3.1 削除コマンド
```
- 3~endまで削除(ストリームに対して)
$ sed '3,$d' myfile

- 実際のファイルから削除する場合
$ sed -i.bak '2d' myfile
```

## 8.3.2 挿入コマンドと追加コマンド
```
挿入(i)
    指定した行やパターンの前に挿入
追加(a)
    指定した行やパターンの後に挿入

$ sed -i '3i\inserted text' test.txt
$ sed -i '3a\append text' test.txt
```

## 8.3.3 変更コマンド
```
sとの違いは?
    cは行全体を変更する

$ sed -i '3c\modified the third line' test.txt
```

## 8.3.4 変換コマンド
```
・パターンや行番号で範囲を指定しない場合、変換処理はストリーム全体となる
・yコマンドは正確な一致が必要で、正規表現のパターンを使用できない。置換後と置換前で文字数は一致していなければいけない

$ sed '1,3y/a/A/' test.txt
```

# 8.4 sedの複数のコマンド
```
-e
    複数条件の指定が可能（セミコロン必須）

$ sed -e 's/Neko/xNyanko/g; 2s/you/I/2' test.txt
```

# 8.5 まとめ
```
sedはレガシー?と呼ばれているみたいだが、速度は遅いにしろ、編集はかなり便利でびっくりした。
数行程度の編集なら、pythonじゃなくてsedでいいかもしれない
${}の方がいいような気もするが
```

# 8.6 練習問題
- 8-1
```
0行
```
- 8-2
```
0行。ストリーム対象なので
```

- 8-3
```
3行目
```

- 8-4
```
ファイルに書き出されないので0行
```