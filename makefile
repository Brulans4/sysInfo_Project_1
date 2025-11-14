CC = gcc
CFLAGS = -std=c11 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE
LDFLAGS = -pthread

SRC = philosophes.c
OBJ = $(SRC:.c=.o)
EXEC = philosophes

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

philosophes.o: philosophes.c philosophes.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(EXEC)
