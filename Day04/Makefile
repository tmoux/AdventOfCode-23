CC = g++-13
CFLAGS = -O2 -std=c++20 -Wall

all: sol

sol: sol.cpp
	$(CC) $(CFLAGS) -o sol sol.cpp

gen: gen.cpp
	$(CC) $(CFLAGS) -o gen gen.cpp

brute: brute.cpp
	$(CC) $(CFLAGS) -o brute brute.cpp

clean:
	$(RM) sol gen brute
