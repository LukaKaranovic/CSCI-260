
CXXFLAGS = -g -Wall -Wextra -Wpedantic -Werror

bst: bstmain.o bst.o
	$(CXX) -o bst bstmain.o bst.o

bstmain.o: bstmain.cpp
	$(CXX) -c $(CXXFLAGS) bstmain.cpp

bst.o: bst.cpp
	$(CXX) -c $(CXXFLAGS) bst.cpp

clean:
	rm -f bst
	rm -f *.o