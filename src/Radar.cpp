//Skeleton of the radar class, based off radar.h
//This is riddled with bugs, i'm sure, it hasn't been tested its just a framework and general idea, almost psuedocode.

#include "Coordinates.h"
#include "Velocity.h"
#include "Airspace.h"
#include <pthread.h>
#include "Radar.h"

using namespace std;

//I'm just winging it here, man. Largely borrowing from pre-existing projects for inspiration/functionality.

Radar::Radar(Airspace* airspaceR,Communication* communcationR){
    //Constructor
    //'Marry' (I guess) the radar with the airspace so it knows where its overlooking?
    this->airspaceR = airspaceR;
    this->communicationR = communcationR; 
    //Marry radar with the communcation system. Maybe This is becasue radar needs
    //Comms to fetch aircraft data? Not sure. Other projects dont seem to do this, unless i'm not seeing something.
    //Uses of this will be figured out later, I guess.
}
Radar::Radar(){
    //empty constructor
}

void Radar::runRadar(){
    //Make the radar do things. Todo.
}

void Radar::scanFlightZone(vector<Aircraft*> airplanes){
    flightsInAirspace.clear();

    for(Aircraft* currentAircraft : airplanes)
    {   //The exact syntax here will almost certainly need to be changed
        if((currentAircraft->getCoordinates.p_x <= Radar::RADAR_WIDTH) && (currentAircraft->getCoordinates.p_y <= Radar::RADAR_LENGTH))
        {
            flightsInAirspace.pushback(currentAircraft); //Flights currently in the area we care about put into the vector
        }
    }
}

void Radar::dispAircraftTooLow(){
    vector<Aircraft*> airplanesTooLow; //create vector to store all aircraft that *are* flying too low

    for(Aircraft* airplane : flightsInAirspace)
    {
        if(airplane->getCoordinates.p_z() <= Radar::MIN_SAFE_ALTITUDE)
            cout << "Aircraft ID: " << airplane->getId() << " is flying too low." << endl;
    }
}

void Radar::dispAircraftAboutToCrash()
{
    //todo
}
