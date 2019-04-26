CXX = clang++-7

FLAGS = --std=c++2a --all-warnings --extra-warnings -Wno-address \
	-Werror -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor -O1

all: tmp tmp/main.o noise

tmp/%.o: %.cpp
	$(CXX) $(FLAGS) -o $@ $<

tmp:
	mkdir $@

clean:
	rm -rf tmp

noise:
	$(shell tmp/main.o \<\<\< $$'1\n2\n3\n4\n5\n\n6\n7\n8\n9\n')

install:
	cp tmp/main.o /usr/bin/agraph
