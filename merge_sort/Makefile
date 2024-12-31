.PHONY: clean

CXX = gcc
FLAGS = -Wall -O2

all: libmerge_sort.a

poc: poc.c libmerge_sort.a merge_sort.h
	$(CXX) $(FLAGS) $< -L. -lmerge_sort -o $@

libmerge_sort.a: merge_sort.o
	ar rcs $@ $^

merge_sort.o: merge_sort.c merge_sort.h
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	rm -f *.o *.a poc
