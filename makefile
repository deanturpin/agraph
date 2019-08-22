CXX ?= clang++-7

FLAGS ?= --std=c++2a --all-warnings --extra-warnings -Wno-address \
	-Werror -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor -O1

all: tmp tmp/agraph

tmp/%.o: %.cpp
	$(CXX) $(FLAGS) -c -o $@ $<

tmp/agraph: tmp/main.o tmp/draw.o
	$(CXX) -o $@ $^

tmp:
	mkdir -p $@

clean:
	rm -rf tmp

noise: tmp/agraph
	./generate.sh | $<

install: tmp/agraph
	cp $< /usr/bin/
