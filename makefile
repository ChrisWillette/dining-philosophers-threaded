#chris willette
#cs360 hw6 (philo)

CC = gcc
CFLAGS = -g -std=gnu99 -Wall -Wextra -pedantic
RANDOM = /encs_share/cs/class/cs360

philo: philo.o random_r.o
	$(CC) $(CFLAGS) random_r.o philo.o -o philo -lpthread -lm

philo.o: philo.c
	$(CC) $(CFLAGS) -c -I$(RANDOM)/include/ philo.c

random_r.o: #random.c random.h
	$(CC) $(CLAGS) -c -I$(RANDOM)/include/ $(RANDOM)/src/random_r.c -lpthread -lm

clean:
	-rm -rf *.o philo
