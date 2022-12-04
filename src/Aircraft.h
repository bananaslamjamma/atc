#pragma once


#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include <vector>
#include "Coordinates.h"
#include "Velocity.h"
#include "math.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/siginfo.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/dispatch.h>

#define PULSE_START 1
#define ATTACH_POINT "AIRCRAFT"


/* We specify the header as being at least a pulse */
/* All of your messages should start with this header */
/* This struct contains a type/subtype field as the first 4 bytes.
 * The type and subtype field can be used to identify the message that is being received.
/ * This allows you to identify data which isn't destined for your server. */
typedef struct _pulse msg_header_t;


/* Our real data comes after the header */
typedef struct AircraftData {
	msg_header_t hdr;
	int id;
    Coordinates coord;
    Velocity velo;
    int arrivalTime;
    int altitude;
    int cmd_type;
} my_data_t;

typedef struct AircraftData_response {
	int response_id;
    Coordinates response_coord;
    Velocity response_velo;
} AircraftData_response;



class Aircraft{

public:
	pthread_t thread_id;
	pthread_mutex_t mutex;
	//should keep p_id and ch_id different
	int ch_id;
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

	int calculateXYDistToOtherAircraft(int = 0, int = 0); //used by radar class w/ default parameters
	int calculateZDistToOtherAircraft(int = 0); //used by radar class w/ default parameters

	void AircraftPrint();
private:
	//double as ch_id for IPC
	int p_id;
	Coordinates grid_pos;
	Velocity velocity;
	int entryTime;
	bool isColliding;
	int server();
	int client();
	//Aircraft collider;

};


#endif
