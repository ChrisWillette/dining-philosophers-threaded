#chris willette
#cs360 hw6 (philo)

CC = gcc
CFLAGS = -g -std=gnu99 -Wall -Wextra -pedantic
RANDOM = /encs_share/cs/class/cs360

philo: philo.o random.o
	$(CC) $(CFLAGS) random.o philo.o -o philo -lm

philo.o: philo.c
	$(CC) $(CFLAGS) -c -I$(RANDOM)/include/ philo.c

random.o: #random.c random.h
	$(CC) $(CLAGS) -c -I$(RANDOM)/include/ $(RANDOM)/src/random.c -lm

clean:
	-rm -rf *.o philo
