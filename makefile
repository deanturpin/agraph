CXX = clang++-7
CX = clang++-7

FLAGS = --std=c++2a --all-warnings --extra-warnings -Wno-address \
	-Werror -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor -O1

all: tmp tmp/aski # noise

tmp/%.o: %.cpp
	$(CXX) $(FLAGS) -o $@ $<

tmp/%.o: %.c
	$(CX) -c -o $@ $<

tmp/aski: main.o
	$(CX) -o $@ $^ -lncurses

tmp:
	mkdir $@

clean:
	rm -rf tmp

# noise:
# 	echo 10 | tmp/main.o

# install:
# 	cp tmp/main.o /usr/bin/agraph

# clang-7 -lcurses -o tmp/aski aski.c
