gcc_options = -std=c++20 -Wall --pedantic-error

SOURCE := main.cpp
#$(patsubst 置換前, 置換後, 対象)
OBJECT := $(patsubst %.cpp,%, $(SOURCE))

$(OBJECT) : $(SOURCE) ../all.h ../all.h.gch
	g++ $(gcc_options) -include ../all.h $< -o $@

../all.h.gch : ../all.h
	g++ $(gcc_options) -x c++-header -o $@ $<

run : ./$(OBJECT)
	./$(OBJECT)

clean :
	rm -f ./$(OBJECT)

.PHONY : run clean

