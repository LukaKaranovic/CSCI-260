CXXFLAGS = -Iinclude/ -Wall -Wextra -Wpedantic -Werror -g 

bin/pex2: build/main.o build/bst.o build/object.o build/redblack.o
	${CXX} -o $@ $^

build/main.o: src/main.cpp 
	${CXX} ${CXXFLAGS} -c $^ -o $@

build/bst.o: src/bst.cpp
	${CXX} ${CXXFLAGS} -c $^ -o $@

build/object.o: src/object.cpp
	${CXX} ${CXXFLAGS} -c $^ -o $@

build/redblack.o: src/redblack.cpp
	${CXX} ${CXXFLAGS} -c $^ -o $@

clean:
	rm -f build/*.o
	rm -f bin/pex2