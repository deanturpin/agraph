CXX = g++-8

FLAGS = --std=c++2a --all-warnings --extra-warnings -Wno-address \
	-Werror -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor -O1

all: tmp tmp/agraph noise

tmp/%.o: %.cpp
	$(CXX) $(FLAGS) -c -o $@ $<

tmp/agraph: tmp/main.o
	$(CXX) $(FLAGS) -o $@ $^

tmp:
	mkdir $@

clean:
	rm -rf tmp

noise:
	tmp/agraph

