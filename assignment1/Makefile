CXXFLAGS = -Iinclude/ -Wall -Wextra -Wpedantic -Werror -g

pex1: build/main.o build/dynamicarray.o build/job.o build/jobqueue.o
	$(CXX) -o bin/pex1 build/main.o build/dynamicarray.o build/job.o build/jobqueue.o

build/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o build/main.o

build/dynamicarray.o: src/dynamicarray.cpp
	$(CXX) $(CXXFLAGS) -c src/dynamicarray.cpp -o build/dynamicarray.o

build/job.o: src/job.cpp
	$(CXX) $(CXXFLAGS) -c src/job.cpp -o build/job.o

build/jobqueue.o: src/jobqueue.cpp
	$(CXX) $(CXXFLAGS) -c src/jobqueue.cpp -o build/jobqueue.o

clean:
	rm -f build/*.o
	rm -f bin/pex1