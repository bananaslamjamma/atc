#ifndef AIRSPACE_H_
#define AIRSPACE_H_

#include <iostream>
#include <string>
#include "Coordinates.h"
#include "Velocity.h"
#include "Airspace.h"
#include "Aircraft.h"
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
	//table of aircraft, id and aircraft object
	//map the id's and planes together
	std::map<int, Aircraft> airspace;
	pthread_mutex_t m_airspace = PTHREAD_MUTEX_INITIALIZER;
};


#endif;
