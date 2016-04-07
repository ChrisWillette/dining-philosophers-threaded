//chris willette
//#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <random_r.h>


#define NUM_PHILOS 5
#define MAX_EAT_TIME 100


typedef struct _philo{
    pthread_t thread;
    int id;
} philo;

pthread_mutex_t chopSticks[NUM_PHILOS]; //locks on the chopsticks
philo philos[NUM_PHILOS]; //philosophers


int eatTime(unsigned int person){
    int interval = randomGaussian_r(9, 3, &person);
    if(interval < 0) interval = 0;
    return interval;
}


int thinkTime(unsigned int person){
    int interval = randomGaussian_r(11, 7, &person);
    if(interval < 0) interval = 0;
    return interval;
}


void* philosophize(void* arg){
    int philoNum = *(int *)arg;
    unsigned int philo_u  = *(unsigned int *)arg;

    int totalEatTime = 0;
    int eatClock;
    int thinkClock;
    int rightStick;
    int leftStick;
    leftStick = philoNum;
    rightStick = philoNum - 1;

    if(philoNum == 0){
	leftStick = NUM_PHILOS - 1;
	rightStick = philoNum;
    }

    while(totalEatTime < 100){
	//grab chopsticks
        pthread_mutex_lock(&chopSticks[leftStick]);
        pthread_mutex_lock(&chopSticks[rightStick]);
	//eat
	eatClock = eatTime(philo_u);
	sleep(eatClock);
        pthread_mutex_unlock(&chopSticks[leftStick]);
        pthread_mutex_unlock(&chopSticks[rightStick]);

	thinkClock = thinkTime(philo_u);
	totalEatTime = totalEatTime + eatClock;
	printf("\nPhilosopher %d now thinking for %d seconds.",
	       philoNum+1, thinkClock);
    }
    printf("\nPhilosopher %d has left the building.\n", philoNum);
    return NULL;
}


int main(){
    int i;
    for(i=0; i<NUM_PHILOS; i++){
        pthread_mutex_init(&chopSticks[i],NULL);
        philos[i].id = i;
    }
    for(i=0;i<NUM_PHILOS;i++){
        pthread_create(&philos[i],NULL,(void *)philosophize,(void *)&philos[i].id);
    }
    for(i=0;i<NUM_PHILOS;i++){
        pthread_join(philos[i],NULL);
    }
    for(i=0;i<NUM_PHILOS;i++){
        pthread_mutex_destroy(&chopSticks[i]);
    }

    printf("\nEveryone's done and left the table.\n\n");
    return 0;
}
