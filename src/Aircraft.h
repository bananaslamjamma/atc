#pragma once


#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include <vector>
#include "Coordinates.h"
#include "Velocity.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>



//this is basically just the aircraft file
class Aircraft{

public:
	pthread_t thread_id;
	Aircraft(int, Coordinates, Velocity, int);
	Aircraft();
	Aircraft(int);
	virtual ~Aircraft();

	void initializeAircraft();

	void setAltitude(int);
	void updateCoordinates();
	int getId();


	Velocity getVelocity();
	Coordinates getCoordinates();
	void setLocation(Coordinates p);
	void setVelocity(Velocity v);
	void setCollision(int);
	int getEntryTime();
	Aircraft getCollider();

	void AircraftPrint();

private:
	int p_id;
	Coordinates location;
	Coordinates grid_pos;
	Velocity velocity;
	int entryTime;
	bool isColliding;
	//Aircraft collider;
	pthread_mutex_t mutex;

};


#endif
