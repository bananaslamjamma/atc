#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include "Aircraft.h"
#include "testPlanes.h"
#include <thread>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>


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

	//pthread_t tid;
	//pthread_create(&tid, NULL, &Aircraft::Aircraft_run, &air);

	//pthread_join(writer.thread_id,NULL);



	std::vector<Aircraft> AH;
	TestPlanes t;

	//Input file structured as: [ArrivalTime], [flightID], [xSpeed], [ySpeed], [zSpeed], [xPos], [yPos], [zPos]

	//std::cout << sizeof(t.testPlaneArr) / sizeof(t.testPlaneArr[0]) << std::endl; //debugging
	for(int i = 0; i < (int) (sizeof(t.testPlaneArr) / sizeof(t.testPlaneArr[0])) ; i++)
	{
		if(i % 8 == 0)
		{
			int appTime, flightID, xPos, xSpeed, yPos, ySpeed, zPos, zSpeed;
			Coordinates tempCoords;
			Velocity tempVel;

			appTime = t.testPlaneArr[i];

			flightID = t.testPlaneArr[i+1];

			xSpeed = t.testPlaneArr[i+2];
			ySpeed = t.testPlaneArr[i+3];
			zSpeed = t.testPlaneArr[i+4];

			xPos = t.testPlaneArr[i+5];
			yPos = t.testPlaneArr[i+6];
			zPos = t.testPlaneArr[i+7];

			tempCoords.p_x = xPos;
			tempCoords.p_y = yPos;
			tempCoords.p_z = zPos;

			tempVel.v_x = xSpeed;
			tempVel.v_y = ySpeed;
			tempVel.v_z = zSpeed;

			//std::cout << "zPos: " << zPos << std::endl; //debugging output

			//create a plane object
			Aircraft tempAircraft(flightID, tempCoords, tempVel, appTime);
			//load it into airCraft vector or maybe just call addAircraft directly?
			//addAircraft(tempAircraft);
			AH.push_back(tempAircraft);
			//std::cout << "aha." << std::endl; //debugging
		}
		else continue;
	}

			for(Aircraft i : AH)
			{
				pthread_join(i.thread_id,NULL);
			}


	return EXIT_SUCCESS;


}


