#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//mutexes
static sem_t connected_lock;
static sem_t operators;
static sem_t ID_lock;

//Global variables
static int NUM_OPERATORS = 2;
static int NUM_LINES = 5;
static int connected = 0;
static int next_id = 0;

void* phonecall(void* vargp) {
   //Synchronize next ID incrementation
   sem_wait(&ID_lock);
   next_id++;
   sem_post(&ID_lock);

   //Set current thread's ID locally
   int callerID = next_id;

   //SIMULATION SECTION --------------------------------------------------------------/>
     //print that an attempt to connect has been made
     printf("Thread %i is attempting to connect...\n", callerID);

     //If line is busy, sleep and then retest until not busy.
     int busy = 1;
     while (busy == 1) {
	sem_wait(&connected_lock);
	//busy
        if (connected == NUM_LINES) {
           sem_post(&connected_lock);
	   sleep(1);
        } else {
	//connected
	   connected++;
	   sem_post(&connected_lock); 
	   break;
        }
     }
        //print that the thread has connected and is ringing
        printf("Thread %i connects to an available line, call ringing...\n", callerID);

     //Wait for an operator to be available
     sem_wait(&operators);
        //print that a question is being taken by an operator
	printf("Thread %i is speaking to the operator\n", callerID);
        //simulate proposal
	sleep(1);
        //print that the thread has asked a question
        printf("Thread %i has proposed a question for the candidates! The operator has left\n", callerID);
     //Disconnect from operator
     sem_post(&operators);

     //disconnect from the line
     sem_wait(&connected_lock);
     connected--;
     sem_post(&connected_lock);

     //print that the thread has hung up
     printf("Thread %i has hung up!\n", callerID); 
     
     //Detatch and self-reap the thread
     pthread_detach(pthread_self());
}

void* timer(void* vargp) {
   //Proper casting and then sleep for given amount of seconds.
   int seconds = *((int*) vargp);
   sleep(seconds);
}

int main (int argc, char** argv) {
   //Initialize the semaphores
   sem_init(&connected_lock, 0, 1);
   sem_init(&operators, 0, 2);
   sem_init(&ID_lock, 0, 1);

   //Initializations and declarations of elements in array of thread id's
   pthread_t phoneCalls[200];
   for (int i=0; i<200; i++) {
      pthread_create(&phoneCalls[i], NULL, phonecall, NULL);
   }

   //Timer that blocks main thread for a number of seconds until debate time finishes
   pthread_t timeThread;
   int seconds = atoi(argv[1]);
   pthread_create(&timeThread, NULL, timer, (void*) &seconds);

   pthread_join(timeThread, NULL);
   
   //Destroy semaphores
   sem_destroy(&connected_lock);
   sem_destroy(&operators);
   sem_destroy(&ID_lock);
    
   //Terminate all threads
   exit(0);
}

