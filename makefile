EXEC = tests

all:
	g++ -std=c++11 -fprofile-arcs -ftest-coverage -O0 src/foundation/context.cpp src/tests/foundation.test.cpp src/tests/math.test.cpp src/math/point.tests.cpp -o $(EXEC)

clean:
	rm $(EXEC)