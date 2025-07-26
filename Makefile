CC = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -ggdb3
LDFLAGS = -lm
.PHONY: clean all

all: build/breakoutt

build:
	mkdir -p build/

build/breakoutt: breakoutt.cpp | build
	$(CC) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -rf build/
