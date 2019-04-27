CXX = clang++-7
CX = clang-7

FLAGS = --std=c++2a --all-warnings --extra-warnings -Wno-address \
	-Werror -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor -O1

all: tmp tmp/aski noise

tmp/%.o: %.cpp
	$(CXX) $(FLAGS) -c -o $@ $<

tmp/aski: tmp/main.o tmp/draw.o
	$(CXX) -o $@ $^

tmp:
	mkdir $@

clean:
	rm -rf tmp

noise: tmp/aski
	./generate.sh | tmp/aski

install: tmp/aski
	cp tmp/aski /usr/bin/

# clang-7 -lcurses -o tmp/aski aski.c
