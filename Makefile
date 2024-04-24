# Adam Veselý | xvesela00
# VUT Fakulta Informačných Technológii
# 3. príklad | Makefile
# 23.04.2024

# !!!!!!!!! Makefile does not detect 4 spaces as a seperator, you need to use tabs only !!!!!!!!!

# Variables --------------------
# C --------------------
CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
CFLAGS_DYN = $(CFLAGS) -fPIC
# C++ --------------------
CXX = g++
CXXFLAGS = -std=c++17 -pedantic -Wall

LDFLAGS = -fsanitize=address
OBJS = htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_statistics.o htab_size.o


# Default settings --------------------

.PHONY: all run clean zip

all: tail wordcount wordcount-dynamic

# Wordcount.cpp --------------------

wordcountcpp: wordcount.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Tail --------------------

tail: tail.c
	$(CC) $(CFLAGS) -o $@ $^

# Wordcount-static --------------

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -o $@ $^

# Wordcount-dynamic --------------

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) -o $@ $^

libhtab.a: $(OBJS)
	ar rcs $@ $^

libhtab.so: $(OBJS)
	$(CC) $(CFLAGS_DYN) -fPIC -shared $^ -o $@

# Wordcount-object --------------

wordcount.o: wordcount.c htab.h io.o
	$(CC) $(CFLAGS_DYN) -c -o $@ $<

# Objects --------------------

htab_bucket_count.o: htab_bucket_count.c htab.h htab_opaque.h
	$(CC) $(CFLAGS_DYN) -c -o $@ $<
# $< is the first dependency (this case io.c)
# -c for object files

htab_clear.o: htab_clear.c htab.h htab_opaque.h
	$(CC) $(CFLAGS_DYN) -c -o $@ $<

htab_erase.o: htab_erase.c htab.h htab_opaque.h
	$(CC) $(CFLAGS_DYN) -c -o $@ $<

htab_find.o: htab_find.c htab.h htab_opaque.h
	$(CC) $(CFLAGS_DYN) -c -o $@ $<

htab_for_each.o: htab_for_each.c htab.h htab_opaque.h
	$(CC) $(CFLAGS_DYN) -c -o $@ $<

htab_free.o: htab_free.c htab.h htab_opaque.h
	$(CC) $(CFLAGS_DYN) -c -o $@ $<

htab_hash_function.o: htab_hash_function.c
	$(CC) $(CFLAGS_DYN) -c -o $@ $<

htab_init.o: htab_init.c htab.h htab_opaque.h
	$(CC) $(CFLAGS_DYN) -c -o $@ $<

htab_lookup_add.o: htab_lookup_add.c htab.h htab_opaque.h
	$(CC) $(CFLAGS_DYN) -c -o $@ $<

htab_statistics.o: htab_statistics.c htab.h htab_opaque.h
	$(CC) $(CFLAGS_DYN) -c -o $@ $<

htab_size.o: htab_size.c htab.h htab_opaque.h
	$(CC) $(CFLAGS_DYN) -c -o $@ $<

io.o: io.c
	$(CC) $(CFLAGS_DYN) -c -o $@ $<

# Running --------------------

run: all
	./tail <tail.c
	./wordcount <wordcount.c
	export LD_LIBRARY_PATH="." && ./wordcount-dynamic <wordcount.c

# Cleaning --------------------

clean:
	rm -f tail wordcount wordcount-dynamic wordcountcpp *.o libhtab.a libhtab.so xvesela00.zip

# Zipping --------------------

zip:
	zip xvesela00.zip *.c *.cc *.h Makefile

# Problem with linker (libhtab.o) -> changed all objects from CFLAGS to CFLAGS_DYN, now it works somehow
