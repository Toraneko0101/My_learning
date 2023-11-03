# 機械語とアセンブラ
```
目標
    ・Cコンパイラから出力されるコードについてのイメージを持つ
```
# CPUとメモリ
- 概要
```
・コンピュータを構成する要素はCPUとメモリに分けられる

メモリ
    データを保持できる場所
CPU
    ・メモリを読み書きしながら処理を行う
    ・CPU目線だと、メモリはランダムアクセス可能な巨大なバイト配列に見える
    ・端から順にアクセスできるのがシーケンシャル
    ・ランダムアクセスは直接かアクセス可能なので便利
    ・CPUがメモリにアクセスするときは数値でメモリのバイト数を指定する（アドレス16から8byteのデータを読む）

CPUが行うこと
    1.次の命令アドレスを内部に保持している
    2.アドレスから命令を読みだし、書いてあることを行う
    3.次の命令を読みだして実行
    ・現在実行中の命令アドレスはプログラムカウンタ(PC)や、インストラクションポインタ(IP)と呼ばれる
    ・CPUが実行するプログラムの形式を機械語という。

プログラムカウンタ
    ・次の実行命令を格納しているメモリ上のアドレスを保持
    ・プログラムが実行されると、命令の長さの分だけプログラムカウンタの値が加算される
    ・分岐命令(branch instruction)でプログラムカウンタを次の命令ではない、任意のアドレスにできる
    ・if文やfor文はこれで実現されている
    ・PCを次の命令以外の場所に設定することをジャンプする、分岐すると呼ぶ


レジスタ
    ・CPUが持っているプログラムカウンタ以外のデータ保存領域
    ・IntelやAMDのプロセッサ(処理装置)には、64bit整数が保持できる領域が16個あり、register(レジスタ)と呼ばれる
    ・メモリはCPUから見ると外部装置なので、読み書きに時間がかかるが、レジスタはCPU内部にあるので、遅延なしのアクセスが可能

機械語の動作
    1. 2つのレジスタの値を使って何らかの演算を行う
    2. その結果をレジスタに書き出す

```
- プログラムの実行手順
```
プログラムの実行
    1. ソースコードを生成
    2. コンパイルで実行可能ファイルを生成
    3. OSがファイルを実行可能なメモリ領域にロード
    4. OSがプログラムを実行するプロセスを生成
    5. 実行に必要なメモリリソース、レジスタ、スタック、ヒープなどの領域を割り当て
    6. プログラムカウンタをプログラムのエントリーポイントに設定し、PCが指すアドレスから次に実行すべき命令が格納されたメモリアドレスを特定、読み取る(fetch)
    7. メモリアドレスから取得したバイナリをマイクロアーキテクチャというコンピュータの内部構造に基づいて実際の命令に変換、解釈。これは命令セットに合わせて設計される(decode)
    8. オペランド（操作対象のデータ）のメモリアドレスを取得（これは命令のオペコードに含まれている）
    9. メモリ内の指定されたアドレスからデータをレジスタに読み込む
    10. 2つのレジスタのデータを演算し、別のレジスタに格納
    11.必要に応じてデータはメモリに戻す
    12.次の命令のメモリアドレスを計算し、次の命令を取得
    13.終った場合は、プロセスを終了し、メモリリソースやほかのリソースを解放
```

- 命令セット
```
命令セットアーキテクチャ(instruction set architecure)
    ・CPUごとに好きにデザインしていい
    ・機械語レベルの互換性が必要なので種類は多くない
    ・PCではx86-64が使われる
    ・AndroidやiPhoneではARMが使われる
```

- x86-64命令セットの名称
```
x86-64
    ・別名：AMD64, Intel64, x64
    ・x86はIntelが作った
    ・64bitに拡張したのがAMD
```

# アセンブラとは
- 概要
```
・機械語は人間にとって理解しにくい
・アセンブラは機械語にほぼ1対1で対応するが読みやすい
・ネイティブなバイナリを出力するコンパイラの場合、アセンブリ出力が目標になる。
・機械語を直接出力しているように見えるコンパイラは、アセンブリを出力した後、bgでアセンブラを起動して機械語にしている
```
- objdumpで実行ファイルを逆アセンブルする
```
objdump
    オブジェクトファイルの情報を表示する
-d 
    命令を含まないすべてのセクションを逆アセンブルする
-m
    逆アセンブルするとき、アーキテクチャを指定する
逆アセンブラ
    機械語をアセンブリに変換すること
```
- hello.cの逆アセンブル
```
hello:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret    

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 9a 2f 00 00    	push   0x2f9a(%rip)        # 3fc0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 9b 2f 00 00 	bnd jmp *0x2f9b(%rip)        # 3fc8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	push   $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    103f:	90                   	nop

Disassembly of section .plt.got:

0000000000001040 <__cxa_finalize@plt>:
    1040:	f3 0f 1e fa          	endbr64 
    1044:	f2 ff 25 ad 2f 00 00 	bnd jmp *0x2fad(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    104b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001050 <__printf_chk@plt>:
    1050:	f3 0f 1e fa          	endbr64 
    1054:	f2 ff 25 75 2f 00 00 	bnd jmp *0x2f75(%rip)        # 3fd0 <__printf_chk@GLIBC_2.3.4>
    105b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001060 <main>:
    1060:	f3 0f 1e fa          	endbr64 
    1064:	48 83 ec 08          	sub    $0x8,%rsp
    1068:	48 8d 35 95 0f 00 00 	lea    0xf95(%rip),%rsi        # 2004 <_IO_stdin_used+0x4>
    106f:	bf 01 00 00 00       	mov    $0x1,%edi
    1074:	31 c0                	xor    %eax,%eax
    1076:	e8 d5 ff ff ff       	call   1050 <__printf_chk@plt>
    107b:	31 c0                	xor    %eax,%eax
    107d:	48 83 c4 08          	add    $0x8,%rsp
    1081:	c3                   	ret    
    1082:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    1089:	00 00 00 
    108c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000001090 <_start>:
    1090:	f3 0f 1e fa          	endbr64 
    1094:	31 ed                	xor    %ebp,%ebp
    1096:	49 89 d1             	mov    %rdx,%r9
    1099:	5e                   	pop    %rsi
    109a:	48 89 e2             	mov    %rsp,%rdx
    109d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    10a1:	50                   	push   %rax
    10a2:	54                   	push   %rsp
    10a3:	45 31 c0             	xor    %r8d,%r8d
    10a6:	31 c9                	xor    %ecx,%ecx
    10a8:	48 8d 3d b1 ff ff ff 	lea    -0x4f(%rip),%rdi        # 1060 <main>
    10af:	ff 15 23 2f 00 00    	call   *0x2f23(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    10b5:	f4                   	hlt    
    10b6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    10bd:	00 00 00 

00000000000010c0 <deregister_tm_clones>:
    10c0:	48 8d 3d 49 2f 00 00 	lea    0x2f49(%rip),%rdi        # 4010 <__TMC_END__>
    10c7:	48 8d 05 42 2f 00 00 	lea    0x2f42(%rip),%rax        # 4010 <__TMC_END__>
    10ce:	48 39 f8             	cmp    %rdi,%rax
    10d1:	74 15                	je     10e8 <deregister_tm_clones+0x28>
    10d3:	48 8b 05 06 2f 00 00 	mov    0x2f06(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    10da:	48 85 c0             	test   %rax,%rax
    10dd:	74 09                	je     10e8 <deregister_tm_clones+0x28>
    10df:	ff e0                	jmp    *%rax
    10e1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    10e8:	c3                   	ret    
    10e9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010f0 <register_tm_clones>:
    10f0:	48 8d 3d 19 2f 00 00 	lea    0x2f19(%rip),%rdi        # 4010 <__TMC_END__>
    10f7:	48 8d 35 12 2f 00 00 	lea    0x2f12(%rip),%rsi        # 4010 <__TMC_END__>
    10fe:	48 29 fe             	sub    %rdi,%rsi
    1101:	48 89 f0             	mov    %rsi,%rax
    1104:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1108:	48 c1 f8 03          	sar    $0x3,%rax
    110c:	48 01 c6             	add    %rax,%rsi
    110f:	48 d1 fe             	sar    %rsi
    1112:	74 14                	je     1128 <register_tm_clones+0x38>
    1114:	48 8b 05 d5 2e 00 00 	mov    0x2ed5(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    111b:	48 85 c0             	test   %rax,%rax
    111e:	74 08                	je     1128 <register_tm_clones+0x38>
    1120:	ff e0                	jmp    *%rax
    1122:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1128:	c3                   	ret    
    1129:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001130 <__do_global_dtors_aux>:
    1130:	f3 0f 1e fa          	endbr64 
    1134:	80 3d d5 2e 00 00 00 	cmpb   $0x0,0x2ed5(%rip)        # 4010 <__TMC_END__>
    113b:	75 2b                	jne    1168 <__do_global_dtors_aux+0x38>
    113d:	55                   	push   %rbp
    113e:	48 83 3d b2 2e 00 00 	cmpq   $0x0,0x2eb2(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1145:	00 
    1146:	48 89 e5             	mov    %rsp,%rbp
    1149:	74 0c                	je     1157 <__do_global_dtors_aux+0x27>
    114b:	48 8b 3d b6 2e 00 00 	mov    0x2eb6(%rip),%rdi        # 4008 <__dso_handle>
    1152:	e8 e9 fe ff ff       	call   1040 <__cxa_finalize@plt>
    1157:	e8 64 ff ff ff       	call   10c0 <deregister_tm_clones>
    115c:	c6 05 ad 2e 00 00 01 	movb   $0x1,0x2ead(%rip)        # 4010 <__TMC_END__>
    1163:	5d                   	pop    %rbp
    1164:	c3                   	ret    
    1165:	0f 1f 00             	nopl   (%rax)
    1168:	c3                   	ret    
    1169:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001170 <frame_dummy>:
    1170:	f3 0f 1e fa          	endbr64 
    1174:	e9 77 ff ff ff       	jmp    10f0 <register_tm_clones>

Disassembly of section .fini:

000000000000117c <_fini>:
    117c:	f3 0f 1e fa          	endbr64 
    1180:	48 83 ec 08          	sub    $0x8,%rsp
    1184:	48 83 c4 08          	add    $0x8,%rsp
    1188:	c3                   	ret    

```
- lsコマンドを逆アセンブルした一部の行に着目する
```
3d58: 48 83 3c 08                   sub rsp,0x8

3d58
    ・機械語が入っているメモリのアドレス
    ・つまり、lsコマンドが実行されるとき、この行の命令はメモリの0x3d58番地に置かれる。
    ・そしてプログラムカウンタが0x3d58の時に実行される

48 83 3c 08  
    ・実際の機械語
    ・CPUはこのデータをfetchして、デコーダで解釈して実行

sub rsp,0x8
    subtract(引く)
    rspというレジスタから0x8(8)を引く
```

# Cとそれに対応するアセンブラ
```c
int main() {
  return 42;
}
```
```
$ gcc -o test1 test1.c
$ ./test1
$ echo $?

$?で直前の終了コードが確認できるのは、shellと同じ
```
- アセンブリに変換して中身を見てみる
```
$ gcc -S test1.s test1.c

	.file	"test1.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$42, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.1.0-8ubuntu1~22.04) 13.1.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
```
- 説明
```
.file	"test1.c"
    ファイル名とバージョン情報。デバッグ情報として使用
.text
    実行可能コードが配置される
.global main
    main関数をグローバルなシンボルとして宣言
.type	main, @function
    シンボルのタイプ情報を指定
.LFB0:
    ・関数の開始を示す

.cfi_startproc
    関数の開始を示すデバッグ情報
    cfa計算用のレジスタがrspに。offsetが0に初期化

endbr64
    コードの実行時にデータの整合性を保つためのセキュリティ命令
pushq %rbp
    スタックに現在のベースポインタ(%rbp)の値をpushして一時退避。スタックポインタを調整することで、呼び出し元のスタックフレーム情報を保持する
.cfi_def_cfa_offset 16
    スタックポインタのオフセットを16byteに設定
    これはスタックにpushされた%rbpのsize
.cfi_offset 6 -16
    6の値を、CFA-16のアドレスに退避。
movq %rsp, %rbp
    スタックポインタ(%rsp)の値をベースポインタ(%rbp)にコピーし、新しいスタックフレームを設定
.cfi_def_cfa_register 6
    %rbpをカノニカルフレームアドレス(cfa)のベースレジスタとして設定。デバッグ情報の一部
movl	$42, %eax
    レジスタ%eaxに値42を設定
popq %rbp
    pushされた%rbpの値をスタックからpopして、元のベースポインタの値を復元
.cfi_def_cfa 7, 7
    スタック上のCFAを設定。デバッグ情報
ret
    関数の戻り値を示す。関数の実行は終了し、%eaxレジスタの値は呼び出し元に返される
.cfi_endproc
    関数の終了を示すデバッグ情報

.LFE0
    ・関数の終了
.size main .-main
    mainのサイズ情報。.mainラベルから.LFEOラベルまでのサイズを計算し、mainのサイズとして設定
.ident
    コンパイラのバージョンや識別情報
.section .note.GNU-stack,"",@progbits
    スタック情報に関するセクション
.section .note.gnu.property,"a"
    プログラムのプロパティに関するセクション
.align 8
    次の命令やデータがメモリ上で8byte境界に配置されるようにアラインメントを調整
.long 1f -0f
    ラベル1とラベル0の間のオフセット(byte数)を示す4byteの整数。デバッグやリンカに関するもの
0: 4:までのラベル
    ラベルは関連するデータや情報を識別する
```
- CFI directive
```
・これはdebug用の命令だが、読みづらい場合は以下のオプションで無効にできる
-fno-asynchronous-unwind-tables

CFI directiveが使われる理由
    ・debug用
    ・スタックポインタ(%rsp)と、ベースポインタ(%rbp)があることで、スタックを巻き戻し、呼び出しフレームアドレスを特定することができる。
```
- スタックポインタ
```
・レジスタ以外にデータを置きたいときがある
・その場合の一時的なデータ置き場をスタック
・一時的に情報を置く番地について格納しているのがスタックポインタ
・スタックポインタはレジスタにある
・プログラムがstackに対してpush,popすると、スタックポインタが変更され、新しいデータがスタックのトップに配置される
・スタックポインタを使用することで、スタック上のデータに効率的にアクセス可能。

```

- 上記のソースファイルに対応した最小構成のアセンブラ
```
.intel_syntax noprefix
.globl main
main:
    mov rax, 42
    ret
```
- 説明
```
.intel_syntax noprefix
    intel記法であることを明言
.globl main
    グローバルなラベルmainを定義
main:
    main関数内のコードを記載
mov rax, 42
    42という値をRAXというレジスタにセット
    raxのaはaccumulatorから来ている
ret
    mainからreturn
    整数を入れられるレジスタは16個あるが、関数からreturnした時にraxに入っているのが返り値というのが約束になっている
```ｌ