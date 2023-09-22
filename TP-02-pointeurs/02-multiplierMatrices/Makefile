include ../../Makefile/common

PROGRAMS=main

all: $(PROGRAMS)

main: main.o matrice.o

#tests: tests.o echangeContenu.o $(TEST_LIB)

#runTests: tests
#	./tests

clean:
	@rm -f *.o $(PROGRAMS)

re: clean all

.PHONY: all clean re
