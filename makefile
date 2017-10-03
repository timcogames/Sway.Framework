EXEC = tests

all:
	g++ -std=c++11 -fprofile-arcs -ftest-coverage -O0 src/tests/main.cpp src/tests/point.tests.cpp src/tests/size.tests.cpp src/tests/rect.tests.cpp -L. -Wl,-Bdynamic -lboost_unit_test_framework -o $(EXEC)

clean:
	rm $(EXEC)