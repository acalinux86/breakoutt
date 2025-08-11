CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -ggdb3
LDFLAGS = -lm
.PHONY: clean all

all: test breakoutt

build:
	mkdir -p build/

build/math_util.o: util/math_util.cpp | build
	$(CXX) $(CXXFLAGS) -c -o $@ $^

breakoutt: build/breakoutt

build/breakoutt: src/breakoutt.cpp build/math_util.o | build
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

run_breakoutt:
	./build/breakoutt

test: build/test

build/test: Test/test.cpp build/math_util.o | build
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

run_test:
	./build/test

clean:
	rm -rf build/
