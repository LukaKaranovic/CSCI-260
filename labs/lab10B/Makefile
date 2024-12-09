CXXFLAGS = -g -Wall -Wextra -Wpedantic -Werror

lab10B: main.o graph.o
	$(CXX) -o lab10B main.o graph.o

main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp

graph.o: graph.cpp
	$(CXX) -c $(CXXFLAGS) graph.cpp

clean:
	rm -f lab10B
	rm -f *.o