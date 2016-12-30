#chris willette


CC = gcc
CFLAGS = -g -std=gnu99 -Wall -Wextra -pedantic


philo: philo.o random_r.o
	$(CC) $(CFLAGS) random_r.o philo.o -o philo -lm -lrt

philo.o: philo.c
	$(CC) $(CFLAGS) -c philo.c

random_r.o: 
	$(CC) $(CLAGS) -c random_r.c -lm -lrt

clean:
	-rm -rf *.o philo
