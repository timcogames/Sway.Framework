EXEC = tests

all:
	g++ -std=c++11 -fprofile-arcs -ftest-coverage -O0 src/foundation/context.cpp src/tests/foundation.tests.cpp src/tests/size.tests.cpp src/tests/point.tests.cpp src/tests/rect.tests.cpp -o $(EXEC)

clean:
	rm $(EXEC)