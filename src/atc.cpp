#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include "Aircraft.h"
#include <thread>



pthread_attr_t attr;

Coordinates setupCoord(int a, int  b , int c){
	Coordinates d;
	d.p_x = a;
	d.p_y = b;
	d.p_z = c;
	return d;
}

Velocity setupVelocity(int a, int b , int c){
	Velocity v;
	v.v_x = a;
	v.v_x = b;
	v.v_x = c;
	return v;
}

int main (int argc, char* argv[]) {

	Coordinates coord1 = setupCoord(1, 2, 3);
	Coordinates coord2 = setupCoord(4, 5, 6);
	Velocity velo1 =  setupVelocity(1, 1, 1);
	Velocity velo2 = setupVelocity(2,2,2);
	Aircraft air(1 , coord1, velo1, 3);
	Aircraft air1(2);
	//Aircraft air2(2);
	//Aircraft air3(3);
	printf("Calling client\n\n");
	air.ping(air.ch_id);
	air1.ping(air1.ch_id);
	//air.ping(air.ch_id);

	pthread_join(air.thread_id,NULL);
	pthread_join(air1.thread_id,NULL);
	//pthread_join(air2.thread_id,NULL);
	//pthread_join(air3.thread_id,NULL);
	return EXIT_SUCCESS;


}


