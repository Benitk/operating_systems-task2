/**
        never get starvation


	we prevent starvation by adding a global variable "turn" that represent Queues every phil has number from 0 to 4
	every loop we letting only the first phil to eat then increment the varibable by one % N(5) by doing that we
	controling the pace and who eat when.. by doing it only one phil eat at a time and it will prevent starvation

	in test function we add to the if equal check if its the right turn for current phil
	in philospher function we check if the number of the phil equal the turn % N if not he cant eat until the right phil finished
	the order of the eating will be 0, 1, 2 ,3 ,4 ,0 ,1 ,2 ,3 ,4 --> and so on
*/
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 

#define N 5 
#define THINKING 2 
#define HUNGRY 1 
#define EATING 0 
#define LEFT (phnum + 4) % N 
#define RIGHT (phnum + 1) % N 

int state[N] = {2, 2, 2, 2, 2}; 
int phil[N] = { 0, 1, 2, 3, 4 }; 

// represent queues
int turn = 0;

sem_t mutex; 
sem_t S[N]; 

void test(int phnum) 
{ 
    //a change here
	if (turn%N == phnum && state[phnum] == HUNGRY 
		&& state[LEFT] != EATING 
		&& state[RIGHT] != EATING) { 
		// state that eating 
		state[phnum] = EATING; 

		sleep(2); 

		printf("Philosopher %d takes fork %d and %d\n", 
					phnum + 1, LEFT + 1, phnum + 1); 

		printf("Philosopher %d is Eating\n", phnum + 1); 

		turn++;
		// sem_post(&S[phnum]) has no effect 
		// during takefork 
		// used to wake up hungry philosophers 
		// during putfork 
		sem_post(&S[phnum]); 
	}
	else{
		sem_post(&S[phnum]);
	}
} 

// take up chopsticks 
void take_fork(int phnum) 
{ 

	sem_wait(&mutex); 

	// state that hungry 
	state[phnum] = HUNGRY; 

	printf("Philosopher %d is Hungry\n", phnum + 1); 

	// eat if neighbours are not eating 
	test(phnum); 

	sem_post(&mutex); 

	// if unable to eat wait to be signalled 
	sem_wait(&S[phnum]); 

	sleep(1); 
} 

// put down chopsticks 
void put_fork(int phnum) 
{ 

	sem_wait(&mutex); 

	// state that thinking 
	state[phnum] = THINKING; 

	printf("Philosopher %d putting forks down\n", phnum + 1); 
	printf("Philosopher %d is thinking\n", phnum + 1); 

	test(LEFT); 
	test(RIGHT); 

	sem_post(&mutex); 
} 

void* philospher(void* num) 
{ 

	while (1) { 

		int* i = num; 

		sleep(1); 
//a change here
		if(turn%N == *i){
			take_fork(*i); 

			sleep(1); 

			put_fork(*i); 
		}
	} 
} 

int main() 
{ 

	int i; 
	pthread_t thread_id[N]; 

	// initialize the semaphores 
	sem_init(&mutex, 0, 1); 

    printf("********************Never get starvation*****************\n");
    sleep(1); 

	for (i = 0; i < N; i++) 

		sem_init(&S[i], 0, 0); 

	for (i = 0; i < N; i++) { 

		// create philosopher processes 
		pthread_create(&thread_id[i], NULL, 
					philospher, &phil[i]); 

		printf("Philosopher %d is thinking\n", i + 1); 
	} 

	for (i = 0; i < N; i++) 

		pthread_join(thread_id[i], NULL); 
} 
