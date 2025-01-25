CC=gcc
CFLAGS=-I. -w -lm 
OBJ = rns.c rng.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

convert: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
