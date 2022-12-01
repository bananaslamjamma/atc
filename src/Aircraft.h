#pragma once


#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include <vector>
#include "Coordinates.h"
#include "Velocity.h"
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>



//this is basically just the aircraft file
class Aircraft{

public:
	Aircraft(int, Coordinates, Velocity, int);
	Aircraft();
	Aircraft(int);
	virtual ~Aircraft();

	void init_Aircraft();

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
	void * Aircraft_run(void *);
	void *dummy(int);
	void test();

private:
	pthread_t thread_id;
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
