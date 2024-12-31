.PHONY: clean

CXX = gcc
FLAGS = -Wall -O2

all: libhash_map.a

poc: poc.c libhash_map.a hash_map.h
	$(CXX) $(FLAGS) $< -L. -lhash_map -o $@

libhash_map.a: hash_map.o
	ar rcs $@ $^

hash_map.o: hash_map.c hash_map.h
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	rm -f hash_map *.o *.a poc
