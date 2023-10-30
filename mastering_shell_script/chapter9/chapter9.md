# 9 Apacheバーチャルホストの自動化

# 9.1 技術要件
```
Apache 2.4x Webサーバのinstallが必要
```
- Debian系なので注釈を見ながらやる
```
apache_install
    $ sudo apt install apache2

serverの起動
    $ sudo systemctl start apache2

System has not been booted with systemd as init system (PID 1). Can't operate.
    ・systemdが正常に起動していない
    ・/etc/wsl.confにsystemd=trueがあるのは確認済み
    ・おそらくストア版のwsl2でないので、wsl --updateする
    ⇒解決

サービスのステータス確認
    $ sudo systemctl status apache2
    activeになっていればOK
    
```

# 9.2 Apacheの名前ベースのvirtual host
```
・Debian系の場合、httpd.confに相当するファイルは
/etc/apache2/apache2.confにある

・systemが提供するファイルからデータを抽出し、それを元にtemplateを作成したい。

virtualhostのテンプレートについては
/etc/apache2/sites-availableに
000-default.confとdefault-ssl.confがある

今回は000-default.confを作業ディレクトリにコピーした
```

## 9.2.1 virtualhostのテンプレートの作成
```
・作業ディレクトリにコピーしてくる
・稼働中の構成ファイルに影響を与えないため
```

## 9.2.2 最初のステップ
```
1. ファイル全体を表示する(pはマッチするパターンを表示。未指定の場合はすべて)
$ sed -n 'p' apache2_test.conf
```

## 9.2.3 行の取り出し
```
・行が固定なら使える
$ sed -n '1,10 p' apache2_test.conf

- 開始タグと終了タグを直接検索する
- 行番号の代わりにPatternを記載できる
$ sed -n '/^<VirtualHost/,/^<\/VirtualHost/p' apache2_test.conf

- 今回は空白文字と#。加えて空行を削除したかったので以下の様にした
$ sed -e '/^\s*#/d; /^$/d' apache2_test.conf

★ 拡張正規表現の場合
$ sed -E '/^(\s*#|$)/d;'  apache2_test.conf > output3.txt
$ buf=$(sed -n '/^\s*#ServerName/p' apache2_test.conf)
$ sed -i "1a\\${buf}" output3.txt
$ sed -i "s/^\s#/\t/" output3.txt

<VirtualHost *:80>
        ServerName www.example.com
        ServerAdmin webmaster@localhost
        DocumentRoot /var/www/html
        ErrorLog ${APACHE_LOG_DIR}/error.log
        CustomLog ${APACHE_LOG_DIR}/access.log combined
</VirtualHost>
```

## 9.2.4 sedスクリプトファイル
```
-f:
    コマンドをスクリプトから読み込むためのオプション

$ sed -nf vh.sed apache2_test.conf 

/*vh.sed*/


/^\s*#/!{
    w template.txt
}

・最初の行で選択した行を指定
・{}で選択される行に対してコマンドを実行する
・sedは否定先読みができなさそう
・ファイルから読み込むときの複数条件の指定がいまいちわからない
```

- 最終的な結論(vh.sh)
```bash
#!/bin/bash
# targetはcurrentにcopyしてきた、/etc/apache2/sites-available/000-default.conf
read -p "target_file: " target


if [ ! -f "$target" ]; then
    echo "${target}は通常ファイルではありません"
    exit 1
fi

output="template.txt"

sed -E '/^(\s*#|$)/d;'  "$target" > "$output"
buf=$(sed -n '/^\s*#ServerName/p' "$target")
sed -i "1a\\${buf}" "$output"
sed -i "s/^\s#/\t/" "$output"
```

# 9.3 バーチャルホストの作成の自動化
```
www.example.comというURLをsales.example.comに置き換える

スクリプトを作成することで、以下を忘れないようにする
    ・DocumentRoot(Webページが納められるディレクトリ)
    ・基本的なコンテンツ

```

- バーチャルホストの有効化、無効化
```
$ sudo a2ensite <hoge.conf>
$ sudo a2dissite <hoge.conf>

・a2ensiteで、/etc/apache2/sites-enabledにシンボリックリンクが追加される。a2dissiteでシンボリックリンクを削除
・/etc/apache2/sites-availableには無効化されているものも含めて作成物がある
" =========================================================================
" Netrw Directory Listing                                        (netrw v17
"   /etc/apache2/sites-enabled
"   Sorted by      name
"   Sort sequence: [\/]$,\<core\%(\.\d\+\)\=\>,\.h$,\.c$,\.cpp$,\~\=\*$,*,\
"   Quick Help: <F1>:help  -:go up dir  D:delete  R:rename  s:sort-by  x:sp
" =========================================================================
../                                                                        
./
host3.conf@  --> /etc/apache2/sites-available/host3.conf
```

- /etc/hosts
```
    ・ホスト名とIPアドレスを対応させるためのファイル
    ・現状、127.0.0.1とhost1.conf等の作成物を対応させているので、localからしか見れない（必要に応じて変える）
```

- vhost.sh
```bash
#!/bin/bash

# passを保持する。数多のwebサイトを収容する予定
WEBDIR=/var/www
# virtual_hostの構成ファイルを保存するために使うCONFDIR変数を初期化
# $CONFDIRの中にファイルを作成する
CONFDIR=/etc/apache2/sites-available
# templateのために使う変数を初期化
TEMPLATE=./template.txt

# もしディレクトリがないなら作成
[ -d $CONFDIR ] || mkdir -p $CONFDIR

# templateファイルの変更と出力(insertじゃないならquoteは要らない)

#servername
sed s/www.example.com/$1/ $TEMPLATE > buf.txt
#serveralias(escapeしている)
sed -i "3c\\\tServerAlias www.${1}.com" buf.txt
#document-root
sed -i "4c\\\tDocumentRoot /var/www/${1}" buf.txt
cp buf.txt "$CONFDIR/$1.conf"
rm buf.txt

# 新しいvirtual_host用webサイトを収容するためのsubディレクトリを作成
mkdir -p "$WEBDIR/$1"

# webサイトのためのindex.htmlを作成する
echo "New site for $1" > "$WEBDIR/$1/index.html"

# ドメイン名を公に登録することを避ける
# sh -c は渡される文字列をコマンドとして実行する。コマンド内で変数の展開も行われる
sudo sh -c "echo 127.0.0.1 www.${1}.com >> /etc/hosts"

# 有効化
sudo a2ensite "${1}.conf"
# 構文エラーがないかcheck
sudo apache2ctl configtest

# apache2をreload
sudo systemctl reload apache2
```

# 補足(Virtualホスト作成自動化までの手順)
```
1. /etc/apache2/sites-available/000-default.confをcurrentにcopyしてくる
2. vh.shを実行。targetはcopyしてきたファイル
3. vhost.shをsudoで実行。引数としてサーバ名を指定(test用なので条件分岐していない)
4. curl www.$1.comで確認

virtualホスト用の構成ファイルは
    vim /etc/apache2/sites-available内に作成され
    $1.confという名がつけられる
```

- 注意点
```
・$HOMEを使う場合は、--preserve-env=HOMEで環境変数を引き継ぐようにしておく。今回は使っていないので問題ない
・原因はsudoで$HOMEが/rootになるから
```

- ベースディレクトリの内容をリスト表示
```
$ ls -R /var/www
/var/www/host3:
index.html

/var/www/html:
index.html
```

## 9.3.1 サイト作成時にデータ入力を促す
```
・virtual_host名以外も設定できるようにしたい
・virtual_hostに関する言葉の意味も調べたい
・sedのi,aコマンドで、データを追加するなど
```
- 追加する具体例
```bash
read -p "Do you want to restrict access to this site? y/n "
[ ${REPLY^^} = 'N' ] && exit 0
read -p "Which network should we restrict access to: " NETWORK

# 行の代わりにPatternを指定。エスケープに注意
sed -i "/<\/VirtualHost>/i <Directory $WEBDIR >\
\n Order allow,deny\
\n Allow from 127.0.0.1\
\n Allow from $NETWORK\
\n</Directory>" $CONFFILE
```

- 修正
```bash
#!/bin/bash

# passを保持する。数多のwebサイトを収容する予定
WEBDIR=/var/www/$1
# virtual_hostの構成ファイルを保存するために使うCONFDIR変数を初期化
# $CONFDIRの中にファイルを作成する
CONFDIR=/etc/apache2/sites-available
CONFFILE=$CONFDIR/$1.conf
# templateのために使う変数を初期化
TEMPLATE=./template.txt

# もしディレクトリがないなら作成
[ -d $CONFDIR ] || mkdir -p $CONFDIR

# templateファイルの変更と出力(insertじゃないならquoteは要らない)

#servername
sed s/www.example.com/$1/ $TEMPLATE > buf.txt
#serveralias
sed -i "3c\\\tServerAlias www.${1}.com" buf.txt
#document-root
sed -i "4c\\\tDocumentRoot ${WEBDIR}" buf.txt
cp buf.txt $CONFFILE
rm buf.txt

# 新しいvirtual_host用webサイトを収容するためのsubディレクトリを作成
mkdir -p "$WEBDIR/$1"

# webサイトのためのindex.htmlを作成する
echo "New site for $1" > "$WEBDIR/index.html"

# ドメイン名を公に登録することを避ける(Allow以下の行があれば不要かも)
sudo sh -c "echo 127.0.0.1 www.${1}.com >> /etc/hosts"

# 有効化
sudo a2ensite "${1}.conf"
# 構文エラーがないかcheck
sudo apache2ctl configtest

# apache2をreload
sudo systemctl reload apache2

# 
read -p "Do you want to restrict access to this site? y/n "
[ ${REPLY^^} = 'N' ] && exit 0
read -p "Which network should we restrict access to: " NETWORK

sed -i "/<\/VirtualHost>/i <Directory $WEBDIR >\
\n Order allow,deny\
\n Allow from 127.0.0.1\
\n Allow from $NETWORK\
\n</Directory>" $CONFFILE
```