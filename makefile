#chris willette
#cs360 hw7 (philo)

CC = gcc
CFLAGS = -g -std=gnu99 -Wall -Wextra -pedantic
RANDOM = /encs_share/cs/class/cs360

philo: philo.o random_r.o
	$(CC) $(CFLAGS) random_r.o philo.o -o philo -lm -lrt

philo.o: philo.c
	$(CC) $(CFLAGS) -c -I$(RANDOM)/include/ philo.c

random_r.o: 
	$(CC) $(CLAGS) -c -I$(RANDOM)/include/ $(RANDOM)/src/random_r.c -lm -lrt

clean:
	-rm -rf *.o philo
