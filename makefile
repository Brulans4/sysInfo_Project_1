CC = gcc
CFLAGS = -std=c11 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE
LDFLAGS = -pthread

PROD_CONS = producer_consumer

SRC = philosophes.c 
OBJ = $(SRC:.c=.o)
EXEC = philosophes producer

PROD_SRC = $(PROD_CONS)/main_producer_consumer.c \
           $(PROD_CONS)/buffer.c \
           $(PROD_CONS)/producer.c \
           $(PROD_CONS)/consumer.c

PROD_OBJ = $(PROD_SRC:.c=.o)

all: clean $(EXEC)

philosophes: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

philosophes.o: philosophes.c philosophes.h
	$(CC) $(CFLAGS) -c $<

producer: $(PROD_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(PROD_CONS)/%.o: $(PROD_CONS)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(PROD_OBJ) $(EXEC)
