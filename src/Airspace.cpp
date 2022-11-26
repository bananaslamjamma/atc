
#include <iostream>
#include "Airspace.h"
#include "Aircraft.h"
#include "Velocity.h"
#include "Coordinates.h"
#include <vector>

using namespace std;


//this is just gonna hold the functions to manipulate the airspace
Airspace::Airspace() {
}

Airspace::~Airspace() {
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
