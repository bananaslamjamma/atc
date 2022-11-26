#pragma once

#ifndef RADAR_H_
#define RADAR_H_

#include "Coordinates.h"
#include "Velocity.h"
#include "Airspace.h"
#include <pthread.h>

using namespace std;

#define INPUT "TODO/todo.txt"

class Radar{
public:
	Radar(Airspace*, Communication*, pthread_attr_t* = nullptr);
	virtual ~Radar();
	pthread_t run();


private:
	pthread_attr_t* tAttr;
	pthread_mutex_t r_mutex;
	pthread_mutexattr_t r_mutex_attr;

};

#endif;
