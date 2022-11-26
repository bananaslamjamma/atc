#pragma once


#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include <vector>
#include "Coordinates.h"
#include "Velocity.h"



//this is basically just the aircraft file
class Aircraft{
public:
	Aircraft(int, Coordinates, Velocity, int);
	Aircraft();
	virtual ~Aircraft();
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

private:
	int p_id;
	Coordinates location;
	Velocity velocity;
	int entryTime;
	bool isColliding;
	//Aircraft collider;
};


#endif
