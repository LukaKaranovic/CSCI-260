CXXFLAGS = -g -Wall -Wextra -Wpedantic -Werror

avl: avlmain.o avl.o
	$(CXX) -o avl avlmain.o avl.o

avlmain.o: avlmain.cpp
	$(CXX) -c $(CXXFLAGS) avlmain.cpp

avl.o: avl.cpp
	$(CXX) -c $(CXXFLAGS) avl.cpp

clean:
	rm -f avl
	rm -f *.o