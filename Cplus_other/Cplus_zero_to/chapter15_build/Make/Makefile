test: test.cpp
	g++ -std=c++20 $^ -o $@

clean:
	rm -f ./test

.PHONY: clean

#階層的に書いておくことで、変更のあったsourceだけをコンパイルしてobjを更新し、リンクを再実行する
#⇒不要なコンパイルを省略⇒ビルド時間を短縮
main: main.o multiple.o
	g++ -std=c++20 $^ -o $@

main.o: main.cpp
	g++ -std=c++20 -c $^

multiple.o: multiple.cpp
	g++ -std=c++20 -c $^