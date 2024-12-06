CXXFLAGS = -Iinclude/ -Wall -Wextra -Wpedantic -Werror -g 

bin/pex3: build/main.o build/graph.o
	${CXX} -o $@ $^

build/main.o: src/main.cpp 
	${CXX} ${CXXFLAGS} -c $^ -o $@

build/graph.o: src/graph.cpp
	${CXX} ${CXXFLAGS} -c $^ -o $@

clean:
	rm -f build/*.o
	rm -f bin/pex3