CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -ggdb3 -o0
LDFLAGS = -lm
.PHONY: clean all

all: breakoutt testvector2 testvector3 testvector4 testmatrix4
run: run_breakoutt run_testvector2 run_testvector3 run_testvector4 run_testmatrix4

build:
	mkdir -p build/

test: build
	mkdir -p build/test

build/math_util.o: util/math_util.cpp | build
	$(CXX) $(CXXFLAGS) -c -o $@ $^

breakoutt: build/breakoutt

build/breakoutt: src/breakoutt.cpp src/breakoutt_main.cpp build/math_util.o | build
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -lGLEW -lSDL2 -lGL

run_breakoutt:
	./build/breakoutt

# Tests
testvector2: build/test/testvector2
build/test/testvector2: Test/TestVector2.cpp build/math_util.o | test
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
run_testvector2:
	./build/test/testvector2

testvector3: build/test/testvector3
build/test/testvector3: Test/TestVector3.cpp build/math_util.o | test
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
run_testvector3:
	./build/test/testvector3

testvector4: build/test/testvector4
build/test/testvector4: Test/TestVector4.cpp build/math_util.o | test
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
run_testvector4:
	./build/test/testvector4

testmatrix4: build/test/testmatrix4
build/test/testmatrix4: Test/TestMatrix4.cpp build/math_util.o | test
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
run_testmatrix4:
	./build/test/testmatrix4

clean:
	rm -rf build/
