#ifndef AIRSPACE_H_
#define AIRSPACE_H_

#include <iostream>
#include <string>
#include "Coordinates.h"
#include "Velocity.h"
#include "Airspace.h"
#include "Aircraft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <map>


using namespace std;


class Airspace{
public:

	Airspace();
	virtual ~Airspace();
	void init();


	void setAircraft();

	void setCollide();
	void addAircraft(Aircraft plane);

	std::vector<Aircraft> getPlanes();
	void delAircraft(int);
	void removePlane();
	void updateAltitude(int, int);
	void updateSpeed(int ,Velocity);
	void updatePlaneLocation();

	void updateAllPlanesPosition();


private:
	//table of aircraft, ID and aircraft object
	//map the ID's and planes together
	std::map<int, Aircraft> airspace;
	pthread_mutex_t m_airspace = PTHREAD_MUTEX_INITIALIZER;
};


#endif
