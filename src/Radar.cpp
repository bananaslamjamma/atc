/*
 * Radar.cpp
 * Unfinished, but theoretically works.
 *
 */

#include "Coordinates.h"
#include "Velocity.h"
#include "Airspace.h"
#include "Radar.h"
#include <pthread.h>


using namespace std;



Radar::Radar(Airspace* airspaceR,Communication* communcationR, pthread_attr_t* thread_attr){
    //Constructor
    //'Marry' (I guess) the radar with the airspace so it knows where its overlooking?
    this->airspaceR = airspaceR;
    this->communicationR = communcationR;
    this->tAttr = thread_attr;
    //Marry radar with the communication system. Maybe This is because radar needs
    //Comms to fetch aircraft data? Not sure. Other projects don't seem to do this, unless i'm not seeing something.
    //Uses of this will be figured out later, I guess.
}

Radar::Radar(){
    //empty constructor, this should never be called?
		airspaceR = nullptr;
	    communicationR = nullptr;
	    tAttr = nullptr;
}

Radar::~Radar() {
}

Radar::~Radar(){} //Deconstructor needed to be declared. Maybe something will be put in here?

void Radar::runRadar(){
	//TODO
    //Make the radar do things.

	//There should probably be some sort of lock here? I dunno. 'getPlanes' performs a lock.
	scanFlightZone(this->airspaceR->getPlanes());
}

void Radar::scanFlightZone(vector<Aircraft*> airplanes){
    this->aircraftInAirSpace.clear();

    for(Aircraft* currentAircraft : airplanes)
    {   //The exact syntax here will almost certainly need to be changed
        if((currentAircraft->getCoordinates().p_x <= Radar::RADAR_WIDTH) && (currentAircraft->getCoordinates().p_y <= Radar::RADAR_LENGTH))
        {
            this->aircraftInAirSpace.push_back(currentAircraft); //Flights currently in the area we care about put into the vector
        }
    }
}

void Radar::dispAircraftTooLow(){
    vector<Aircraft*> airplanesTooLow; //create vector to store all aircraft that *are* flying too low
/***
 *
 *
 *     for(Aircraft* airplane : aircraftInAirSpace)
    {
        if(airplane->getCoordinates().p_z <= Radar::MIN_SAFE_ALTITUDE)
            cout << "Aircraft ID: " << airplane->getId() << " is flying too low." << endl;
    }
 *
 *
 */

}

void Radar::dispAircraftAboutToCrash()
{
	for (Aircraft* firstAircraft : aircraftInAirSpace)
	{
			int xPosFirstA = firstAircraft->getCoordinates().p_x;
			int yPosFirstA = firstAircraft->getCoordinates().p_y;
			int zPosFirstA = firstAircraft->getCoordinates().p_z;

			for (Aircraft* secondAircraft: aircraftInAirSpace)
			{
				if(firstAircraft == secondAircraft) continue;
				else if(secondAircraft->calculateXYDistToOtherAircraft(xPosFirstA, yPosFirstA) <= Radar::MIN_HORI_DIST_AIRCRAFT)
				{
					if(secondAircraft->calculateZDistToOtherAircraft(zPosFirstA) <= Radar::MIN_VERT_DIST_AIRCRAFT )
					{
						cout << "\n Plane ID: " << firstAircraft->getId() << " will crash with plane id "<< secondAircraft->getId() << endl;
					}else continue;
				}
			}
	 }
}
