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
			tem//pVel.v_y = ySpeed;
			tempVel.v_z = zSpeed;

			//std::cout << "zPos: " << zPos << std::endl; //debugging output

			//create a plane object
			Aircraft tempAircraft(flightID, tempCoords, tempVel, appTime);
			//load it into airCraft vector or maybe just call addAircraft directly?
			//addAircraft(tempAircraft);
			AH.//push_back(tempAircraft);
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


