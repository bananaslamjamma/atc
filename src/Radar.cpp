//Skeleton of the radar class, based off radar.h
//This is riddled with bugs, i'm sure, it hasn't been tested its just a framework and general idea, almost psuedocode.

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
		this->airspaceR = nullptr;
	    this->communicationR = nullptr;
	    this->tAttr = nullptr;
}

void Radar::runRadar(){
    //Make the radar do things. TODO.
}

void Radar::scanFlightZone(vector<Aircraft*> airplanes){
    this->flightsInAirSpace.clear();

    for(Aircraft* currentAircraft : airplanes)
    {   //The exact syntax here will almost certainly need to be changed
        if((currentAircraft->getCoordinates().p_x <= Radar::RADAR_WIDTH) && (currentAircraft->getCoordinates().p_y <= Radar::RADAR_LENGTH))
        {
            this->flightsInAirSpace.push_back(currentAircraft); //Flights currently in the area we care about put into the vector
        }
    }
}

void Radar::dispAircraftTooLow(){
    vector<Aircraft*> airplanesTooLow; //create vector to store all aircraft that *are* flying too low

    for(Aircraft* airplane : flightsInAirspace)
    {
        if(airplane->getCoordinates().p_z <= Radar::MIN_SAFE_ALTITUDE)
            cout << "Aircraft ID: " << airplane->getId() << " is flying too low." << endl;
    }
}

void Radar::dispAircraftAboutToCrash()
{
    //TODO
}
