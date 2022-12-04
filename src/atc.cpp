#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include "Aircraft.h"
#include <thread>



pthread_attr_t attr;


void *threadDefault (void *arg) {
	printf("A thread with default attributes is created\n\n");
	return NULL;
}

void *threadCustomized (void *arg) {
	int policy;
	int detachstate;
	printf("A thread with customized attributes is created!\n");

	/* Print out dtach state */
	pthread_attr_getdetachstate(&attr, &detachstate);
	printf ("   Detach state: %s\n",
	(detachstate == PTHREAD_CREATE_DETACHED) ?
	"PTHREAD_CREATE_DETACHED" :
	(detachstate == PTHREAD_CREATE_JOINABLE) ?
	"PTHREAD_CREATE_JOINABLE" : "???");

	/* Print out scheduling policy*/
	pthread_attr_getschedpolicy(&attr, &policy);
	printf ("   Scheduling policy: %s\n\n",
	(policy == SCHED_OTHER) ? "SCHED_OTHER" :
	(policy == SCHED_FIFO)	? "SCHED_FIFO"  :
	(policy == SCHED_RR)	? "SCHED_RR" 	:
	"???");

	pthread_exit(NULL);
	return NULL;
}

void * old(){
	pthread_t threadD, threadC, threadA;
		Aircraft air(5);
		air.AircraftPrint();
		int rc;
		/* Initialize attributes */
		rc = pthread_attr_init(&attr);
		if (rc)
			printf("ERROR, RC from pthread_attr_init() is %d \n", rc);

		/* Set detach state */
		rc = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		if (rc)
			printf("ERROR; RC from pthread_attr_setdetachstate() is %d \n", rc);



		/* Creating thread with default attributes */
		rc = pthread_create (&threadD, NULL, threadDefault, NULL);
		if (rc)
			printf("ERROR when creating default thread; Code is %d\n", rc);

		/* Creating thread with constructed attribute object */
		rc = pthread_create(&threadC, &attr, threadCustomized, NULL);



		if (rc)
			printf("ERROR when creating customized thread; Code is %d \n", rc);

		/* Synchronize all threads */
		pthread_join(threadD, NULL);
		pthread_join(threadC, NULL);

		/* Free up attribute object and exit */
		pthread_attr_destroy(&attr);
		pthread_exit(NULL);

}

int main (int argc, char* argv[]) {
	Aircraft air(0);
	Aircraft air1(2);
	Aircraft air2(3);
	Aircraft air3(4);

	//pthread_t tid;
	//pthread_create(&tid, NULL, &Aircraft::Aircraft_run, &air);

	//pthread_join(writer.thread_id,NULL);
	pthread_join(air.thread_id,NULL);
	pthread_join(air1.thread_id,NULL);
	pthread_join(air2.thread_id,NULL);
	pthread_join(air3.thread_id,NULL);
	return EXIT_SUCCESS;


}


