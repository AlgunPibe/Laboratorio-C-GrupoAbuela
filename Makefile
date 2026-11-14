CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJ = main.o artemis.o validaciones.o

artemis: $(OBJ)
	$(CC) $(CFLAGS) -o artemis $(OBJ) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o artemis
