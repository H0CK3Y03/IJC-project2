# Adam Veselý | xvesela00
# VUT Fakulta Informačných Technológii
# 3. príklad | Makefile
# 23.04.2024
CC = gcc
CFLAGS =

.PHONY: all run clean clean_test

all: tail.c wordcount.c

default_target: all

tail: tail.c
    $(CC) $(CFLAGS) -o $@ $^

wordcount: wordcount.c
    $(CC) $(CFLAGS) -o $@ $^

run: all
    ./tail
    ./wordcount

clean:
    rm -f tail wordcount

clean_test:
    @rm -rf io-test.c io-test .o.sh io_tests2024 tail_tests2024 wordcount_tests2024 tail libhtab.a libhtab.so wordcount wordcount- wordcount-dynamic && cd tmp && mv Makefile .. && cd .. && rmdir tmp

clean_all: clean clean_test
    rm -f xvesela00.zip

zip:
    zip xvesela00.zip *.c *.h *.a *.so Makefile