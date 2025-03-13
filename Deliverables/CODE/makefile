CC = gcc
CFLAGS = -Wall -Wextra

PROGRAMS = scheduler

all: $(PROGRAMS)

rng: scheduler.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(PROGRAMS)