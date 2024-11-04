CC = gcc
CFLAGS = -Wall -g
LIBS = -lbcm2835

all: binary_counter

binary_counter: main.o gpio_input.o
	$(CC) $(CFLAGS) -o binary_counter main.o gpio_input.o $(LIBS)

main.o: main.c gpio_input.h
	$(CC) $(CFLAGS) -c main.c

gpio_input.o: gpio_input.c gpio_input.h
	$(CC) $(CFLAGS) -c gpio_input.c

clean:
	rm -f binary_counter *.o
