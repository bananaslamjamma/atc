
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Airspace.h"
#include "Aircraft.h"
#include "Velocity.h"
#include "Coordinates.h"
#include <vector>
#include <string>

using namespace std;

#define PLANEFILE "testPlanes.txt"

//this isn't really an "airspace"
// it manages a data structure filled with aircrafts really


Airspace::Airspace() {
	//just have the mutex here
	pthread_mutexattr_t attr;
	/* synchronization stuff */
	pthread_mutexattr_init(&attr);
	//lock count
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	//mutex init
	pthread_mutex_init(&this->m_airspace, &attr);
}



Airspace::~Airspace() {
}

// i'll have this read the input file
void Airspace::init(){
//read test cases from a .txt file and load them into a vector of airplanes
ifstream planeFile;
planeFile.open(PLANEFILE);

//Declare temporary variables
int appTime, xPos, xSpeed, yPos, ySpeed, zPos, zSpeed;
string flightID;
Coordinates tempCoords;
Velocity tempVel;

//Input file structured as: [ArrivalTime], [flightID], [xSpeed], [ySpeed], [zSpeed], [xPos], [yPos], [zPos]
	while(getLine(planeFile, appTime )) //check if there's still another plane to load
	{
		//get data out of the file
		planeFile >> appTime >> flightID >> xSpeed >> ySpeed >> zSpeed >> xPos >> yPos >> zPos;
		//create coordinates and velocity objects
		tempCoords.p_x = xPos;
		tempCoords.p_y = yPos;
		tempCoords.p_z = zPos;

		tempVel.v_x = xSpeed;
		tempVel.v_y = ySpeed;
		tempVel.v_z = zSpeed;

		//create a plane object
		Aircraft tempAircraft(flightID, tempCoords, tempVel, appTime);
		//load it into airCraft vector or maybe just call addAircraft directly?
		addAircraft(tempAircraft);

	}
		//Verify this information somehow? It would be a debugging functionality only.
		//This should in theory work, barring any syntax errors.
}

// run()
// funct to update each flight's position
void Airspace::updateAllPlanesPosition(){


}

// run()
// funct to update each flight's position
void Airspace::updateAllPlanesPosition(){


}



//add aircraft to the air space
void Airspace::addAircraft(Aircraft plane) {
	pthread_mutex_lock(&m_airspace);
	int id =  plane.getId();
	//add a plane to the airspace
	airspace.insert(std::pair<int, Aircraft>(id, plane));
	pthread_mutex_unlock(&m_airspace);

}


//return a vector of airplanes within the airspace
std::vector<Aircraft> Airspace::getPlanes(){
	std::vector<Aircraft> outputAircraft;
	pthread_mutex_lock(&m_airspace);

	for (const auto &plane: airspace){
		//push back into vector
		outputAircraft.push_back(plane.second);
	}
	pthread_mutex_unlock(&m_airspace);
	return outputAircraft;
}

//delete an aircraft from the airspace
void Airspace::delAircraft(int id) {
	pthread_mutex_lock(&m_airspace);
	airspace.erase(id);
	pthread_mutex_unlock(&m_airspace);
}

void Airspace::updateAltitude(int id, int alt) {
	pthread_mutex_lock(&m_airspace);
	try{
		airspace.at(id).setAltitude(alt);
	} catch(std::out_of_range& e){
	}
	pthread_mutex_unlock(&m_airspace);
}

void Airspace::updateSpeed(int id, Velocity velo) {
	pthread_mutex_lock(&m_airspace);
	try{
		airspace.at(id).setVelocity(velo);
	} catch(std::out_of_range& e){
	}
	pthread_mutex_unlock(&m_airspace);
}

void Airspace::updatePlaneLocation() {
	pthread_mutex_lock(&m_airspace);
	for (auto &plane : airspace){
		plane.second.updateCoordinates();
	}
	pthread_mutex_unlock(&m_airspace);
}
