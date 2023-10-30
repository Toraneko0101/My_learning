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

# ドメイン名を公に登録することを避ける
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