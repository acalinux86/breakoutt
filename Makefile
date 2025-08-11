CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -ggdb3
LDFLAGS = -lm
.PHONY: clean all

all: testvector2 testvector3 breakoutt
run: run_breakoutt run_testvector3 run_testvector2

build:
	mkdir -p build/

build/math_util.o: util/math_util.cpp | build
	$(CXX) $(CXXFLAGS) -c -o $@ $^

breakoutt: build/breakoutt

build/breakoutt: src/breakoutt.cpp build/math_util.o | build
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

run_breakoutt:
	./build/breakoutt

# Tests
testvector2: build/testvector2
build/testvector2: Test/TestVector2.cpp build/math_util.o | build
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
run_testvector2:
	./build/testvector2

testvector3: build/testvector3
build/testvector3: Test/TestVector3.cpp build/math_util.o | build
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
run_testvector3:
	./build/testvector3

clean:
	rm -rf build/
