# アクセスするために使われたブラウザ情報
{ browser[$12]++ }
END {
    for (b in browser){
        print b, " has accessed ", browser[b], " times."
    }
}