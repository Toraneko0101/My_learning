# 6 ループを使った反復処理

# 6.1 forループ
```
$ type for
for is a shell keyword

・forはシェルキーワードであり、スクリプト内で使ったり、コマンドライン上で直接使うこともできる。
・シェルキーワードはスクリプトの構文と制御構造を操作するために使用される
```
- ユーザパスワード(コード)
```bash
sudo -i
for u in bob joe; do
    useradd $u
    echo "$u:Password1" | chpasswd
    passwd -e $u
done
```
- ユーザパスワード(説明)
```
useradd:
    ユーザの作成
chpasswd:
    ・複数のパスワードをバッチモードで更新
    ・root権限が必要。非対話的
    ・echo "username:password" | chpasswdのようにpassを変更できる
    ・ファイルに記載して、catしたデータを渡すこともできる。コマンド履歴に残らないのでそっちの方がいい
passwd -e username:
    指定したユーザアカウントのパスワードを期限切れにする。

```
- sudo -iとsudo su -の違いについて
```
sudo
    ・他のユーザの権限でプログラムを実行するコマンド
    ・sudo -i: ログインシェルとして指定されているシェルを実行

su
    他のユーザにスイッチする管理系のコマンド。

環境変数をクリアする意味合いだとsu -の方が強そう


```
- ディレクトリ内のファイル処理（コード）
```bash
#!/bin/bash
for f in *; do
    stat "$f"
done
```
```
File: hello1.sh
  Size: 52          Blocks: 8          IO Block: 4096   通常ファイル
Device: 810h/2064d  Inode: 80044       Links: 1
Access: (0755/-rwxr-xr-x)  Uid: ( 1000/toraneko)   Gid: ( 1000/toraneko)
Access: 2023-10-29 09:20:47.997478316 +0900
Modify: 2023-10-29 09:20:47.967478316 +0900
Change: 2023-10-29 09:20:47.967478316 +0900
 Birth: 2023-10-28 20:48:47.174245179 +0900
```
- ディレクトリ内のファイル処理（説明）
```
stat:
    ファイルの属性や日付などを表示
*:
    ディレクトリ内のすべてのファイルを処理する
```

- Ubuntuの日本語化
```
$ sudo apt install language-pack-ja
$ sudo dpkg-reconfigure locales
$ exit
```
- bashシェルを使用しているユーザのカレントを調べるためのスクリプト
```bash
#!/bin/bash
for user in $(who | cut -f1 -d" "); do
    lsof -u "$user" -a -c bash | grep cwd
done
```
- 補足
```
cut -f1 -d " " 
    1行ずつ-dで指定された区切り文字に渡し、その1つ目を抽出する。
lsof(list open files):  
    開かれているファイルをリスト表示する
    lsof -u "$user" -a -c bash | grep cwd
    -u "$user"
        特定のユーザによって開かれているファイルを検索
    -c bash
        プロセスのコマンド名がbashのものだけを抽出
    grep cwd
        カレントディレクトリを含む行のみを表示

・結果として各ユーザごとに、bashシェルプロセスがどのディレクトリで作業しているか確認可能
```
- 結果
```
bash    8431 toraneko  cwd    DIR   8,16     4096 80043 /home/toraneko/program_file/my_learning/mastering_shell_script/chapter6/bin

```

- サンプルプログラム
```bash
#!/bin/bash

echo "You are using $(basename $0)"
for n in "$@"; do
    echo "Hello $n"
done

exit 0
```

# 6.2 高度なforループ
```
値にスペースが含まれる場合は二重引用符を使用するべき
区切り文字がスペース以外であったり、複数行ファイルの場合は6.3を見ること
```
- 例
```bash
#!/bin/bash

for var in "one" "This is two" "Now three" "We'll check four"; do
    echo "Value: $var"
done
```
# 6.3 IFS(internal field separator: 内部フィールドセパレータ)
```bash
#!/bin/bash

file="test.txt"
IFS=$'\n'
for var in $(cat $file); do
    echo " $var"
done
```
- 解説
```
IFS変数の値
    ・デフォルトは、スペースとタブと改行
    ・IFS=$'\n'とする事で、改行だけを区切り文字として認識する
    ・$と、クォートを付けているのはbashがデフォルトで\r,\n,\t等のエスケープ文字を解釈しないため。ダブルクォートでは解釈されないので注意
```

# 6.4 ディレクトリとファイルのチェック
```bash
#!/bin/bash

for path in /home/toraneko/*; do
    if [ -d "$path" ]; then
        echo "$path is a directory"
    elif [ -f "$path" ]; then
        echo "$path is a file"
    fi
done
```

# 6.5 C言語スタイルのforループ
```
python使いとしては、上のようなforループも好きだけど
```
```bash
#!/bin/bash

for (( v=1; v<=10; v++)); do
    echo "Value is $v"
done
```

# 6.6 入れ子ループ
```bash
#!/bin/bash

for (( i=1; i<=3; i++)); do
    echo "First loop $i"
    for (( j=1; j<=3; j++)); do
        echo "Second loop $j"
    done
done
```

# 6.7 ループの出力結果のリダイレクト
```bash
#!/bin/bash

for (( i=1; i<=5; i++)); do
    echo "$i"
done > test1.txt
```

## 6.7.1 ループの制御
- ディレクトリのみを半角区切りで表示
```bash
#!/bin/bash
# && break等も使える
for f in /home/toraneko/*; do
    [ -d "$f" ] || continue
    dir_name="$dir_name $f"
done
echo $dir_name
```

# 6.8 whileループとuntilループ
- while(真である限り繰り返す)
```bash
#!/bin/bash

count=10
while (( count>=0 )) ; do
    echo -e "$count \c"
    (( count-- ))
done ; echo
```
- until(真になるまで繰り返す)
```bash
#!/bin/bash

count=10
until (( count<0 )) ; do
    echo -e "$count \c"
    (( count-- ))
done ; echo
```
- 補足
```
\cで改行を読み込まないようにしているので、doneの後で改行しておく
```
# 6.9 ファイルからの入力の読み込み
```bash
#!/bin/bash

if [ ! -f "$1" ]; then
    echo "The input to $0 should be a filename"
    exit 1
fi

echo "The following server are up on $(date +%x)" > server.out
while read server; do
    ping -c1 "$server" && echo "Server up: $server" >> server.out
done < "$1"

cat server.out
```
- 説明
```
date +%x
    +はformat指定で結果を出力
    %xは日付となる
while read server; do
done < "$1"
    $1で指定したファイルの各行をserverに代入

pingについては以前触れているため省略。
```

# 6.10 オペレータ用メニューの作成
```
・限られたシェルの機能しか要らない人たち向けの選択メニューを作る
```
- コード
```bash
#!/bin/bash

while true; do
    clear
    echo "Choose an item: a, b or c"
    echo "a: Backup"
    echo "b: Display Calendar"
    echo "c: Exit"
    #-s 標準入力から変数に代入する
    read -sn1

    case "$REPLY" in
        a) tar -czvf ../backup.tgz ../bin;;
        b) cal;;
        c) exit 0;;
    esac
    read -n1 -p "Press any key to continue"
done
```
- 補足
```
上記のスクリプトを実行する際、
$ exec file.sh
という風にすると、ユーザがshによる操作を完了したときに、シェルは残らなくなる

exec
    ・同じプロセス内で外部コマンドが実行される
    ・余分なプロセスを作成しないので便利

たとえば
exec lsとすると、execによって、新しいプロセスは作成されず、現在のプロセスがlsコマンドに置き換えられる。そのためlsコマンドの実行が終わるとシェルも終了する。
```

# 6.11 まとめ?
- Bashの括弧について復習する

- [] bracket
```
testの短縮形。コマンド
```

- [[]] double bracket
```
・正規表現やパラメータマッチが可能
・変数の単語が分割されない
・キーワード
```

- ()
```
サブシェルで記述されたコマンドを実行
サブシェルの状態は親シェルには影響を与えない
```

- $()
```
コマンド置換
コマンド内の結果を文字列として返す
バッククォートと違い、ネスト可能
```

- (())
```
算術演算
```

- {}
```
・変数展開
・変数名と文字列を区別する際に使う
${hello}neko
・2桁以上の位置パラメータを表す際にも使う
${10}
・デフォルトパラメータでもある
${1-default}
```
- コマンド群の実行
```
・まとめて実行してそれをリダイレクト
・関数での使用例もある
・あとはTry-catchなど
```

- C補足
```bash
#!/bin/bash

for ((x=1; x<=3; x++)){
    echo $x
}
```
```
bashの場合、do~doneの代わりに{}が使える。
```





# 6.12 練習問題
- 6-1
```
ファイルにリダイレクトされるので0行
```
- 6-2
```
4
```
- 6-3
```
,を;にする
```
- 6-4
```
無限ループする
```
- 6-5
- 