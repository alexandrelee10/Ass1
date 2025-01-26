CC = gcc
CFLAGS = -Wall -Wextra

PROGRAMS = rng rns

all: $(PROGRAMS)

rng: rng.o
	$(CC) $(CFLAGS) -o $@ $^

rns: rns.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(PROGRAMS)
