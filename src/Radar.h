#pragma once

#ifndef RADAR_H_
#define RADAR_H_

#include "Coordinates.h"
#include "Velocity.h"
#include "Airspace.h"
#include "Aircraft.h"
#include <pthread.h>
#include "Communication.h"

using namespace std;

//#define INPUT "TODO/todo.txt" //Left this out for now, probably useless?

class Radar{
public:
	Radar(Airspace*, Communication*, pthread_attr_t* = nullptr);
	virtual ~Radar();
	pthread_t run(); //im not so sure this should be here?
	void scanFlightZone(vector<Aircraft*>); //assuming this function will recieve a vector of pointers to aircraft objects
	void dispAircraftCrashing();
	void dispAicraftLow();

	//lets declare some constants that will probably  be useful
	const int static MIN_RADAR_HEIGHT = 15000;
	const int static MAX_RADAR_HEIGHT = 40000; //Min height + height of flight zone (25000)
	const int static MIN_SAFE_ALTITUDE = 15000; //Same as minimum height of tracking area
	const int static MIN_HORI_DIST_AIRCRAFT = 3000; //3000 Units in width/length (x,y) directions, as per project outline
	const int static MIN_VERT_DIST_AIRCRAFT = 1000;	//1000 Units in depth (z) direction, As per project outline
	const int static RADAR_WIDTH = 100000; //As per project outline
	const int static RADAR_LENGTH = 100000; //As per project outline
	//add more here as needed.

private:
	pthread_attr_t* tAttr;
	pthread_mutex_t r_mutex;
	pthread_mutexattr_t r_mutex_attr;

	Airspace* airspaceR;
	Communication* communicationR;
	vector<Aircraft*> flightsInAirSpace //example program has this public, why?

};

#endif;
