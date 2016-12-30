//chris willette
//#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "random_r.h"
#include <unistd.h>

#define NUM_PHILOS 5
#define MAX_EAT_TIME 100

pthread_mutex_t chopSticks[NUM_PHILOS]; //locks on the chopsticks
pthread_t philos[NUM_PHILOS];
int philos_id[NUM_PHILOS];

void* dinner(void* arg){
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

  while(totalEatTime < MAX_EAT_TIME){
    
    thinkClock = randomGaussian_r(9, 3, &philo_u);
    if(thinkClock < 0) thinkClock = 0;
    printf("\nPhilosopher %d now thinking for %d seconds.",
	   philoNum+1, thinkClock);
    sleep(thinkClock); 
    //grab chopsticks
    pthread_mutex_lock(&chopSticks[leftStick]);
    pthread_mutex_lock(&chopSticks[rightStick]);
    //eat
    eatClock = randomGaussian_r(11, 7, &philo_u);
    if(eatClock < 0) eatClock = 0;
    printf("\nPhilosopher %d now eating for %d seconds.", 
	   philoNum+1, eatClock);
    sleep(eatClock);     
    totalEatTime = totalEatTime + eatClock;
    pthread_mutex_unlock(&chopSticks[leftStick]);
    pthread_mutex_unlock(&chopSticks[rightStick]);
  }
  printf("\nPhilosopher %d has left the building.\n", philoNum+1);
  return NULL;
}


int main(){
  int i;
  for(i=0; i<NUM_PHILOS; i++){
    pthread_mutex_init(&chopSticks[i],NULL);
    philos_id[i] = i;
  }
  for(i=0;i<NUM_PHILOS;i++){
    pthread_create(&philos[i],NULL, dinner,(void *)&philos_id[i]);
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
