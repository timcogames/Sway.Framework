EXEC = tests

all:
	g++ -std=c++11 -fprofile-arcs -ftest-coverage -O0 src/foundation/context.cpp src/tests/foundation.test.cpp -o $(EXEC)

clean:
	rm $(EXEC)