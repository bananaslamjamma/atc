#pragma once

#ifndef RADAR_H_
#define RADAR_H_

#include "Coordinates.h"
#include "Velocity.h"
#include "Airspace.h"
#include "Aircraft.h"
#include <pthread.h>

using namespace std;

#define INPUT "TODO/todo.txt"

class Radar{
public:
	Radar(Airspace*, Communication*, pthread_attr_t* = nullptr);
	virtual ~Radar();
	pthread_t run();

	//lets declare some constants that will probably  be useful
	const int static MIN_RADAR_HEIGHT = 15000;
	const int static MAX_RADAR_HEIGHT = 40000; //Min height + height of flight zone (25000)
	const int static MIN_SAFE_ALTITUDE = 15000; //Same as minimum height of tracking area
	
private:
	pthread_attr_t* tAttr;
	pthread_mutex_t r_mutex;
	pthread_mutexattr_t r_mutex_attr;

};

#endif;
