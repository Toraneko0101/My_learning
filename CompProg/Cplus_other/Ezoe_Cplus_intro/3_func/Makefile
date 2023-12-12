gcc_options = -std=c++20 -Wall --pedantic-error

program : main.cpp ../all.h ../all.h.gch
	g++ $(gcc_options) -include ../all.h $< -o $@

../all.h.gch : ../all.h
	g++ $(gcc_options) -x c++-header -o $@ $<

run : program
	./program

clean :
	rm -f ./program

.PHONY : run clean

