CC=gcc
CFLAGS=-Wall -Wextra -pthread

all: diningPhilosophers

diningPhilosophers: diningPhilosophers.o
	$(CC) $(CFLAGS) $< -o $@

diningPhilosophers.o: diningPhilosophers.c diningPhilosophers.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o diningPhilosophers

run:
	./diningPhilosophers
