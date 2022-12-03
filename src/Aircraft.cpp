#include "Aircraft.h"
#include "math.h"
#include <iostream>

using namespace std;

//make a copy of this constructor for a threaded version
Aircraft::Aircraft(int id, Coordinates po, Velocity ve, int entryT) {
	p_id = id;
	grid_pos = po;
	velocity = ve;
	entryTime = entryT;
	isColliding = false;
}

Aircraft::Aircraft(){

}

//debugging
Aircraft::Aircraft(int id){

	p_id = id;
	Coordinates dummy;
	Velocity dummy_v;
	dummy.p_x = 1;
	dummy.p_y = 2;
	dummy.p_z = 3;
	dummy_v.v_x = 3;
	dummy_v.v_y = 2;
	dummy_v.v_z = 1;

	initializeAircraft();
}




Aircraft::~Aircraft() {
	pthread_mutex_destroy( &mutex );
	thread_id = NULL;

}

// you need to call another instance of
void * Aircraft_run(void *arg){
	Aircraft& air = *(Aircraft*) arg;
	air.AircraftPrint();
	sleep(5);
	cout << "waking up";
	//pthread_exit(NULL);
	return NULL;
}

void Aircraft::initializeAircraft(){
	int rc;

	if(pthread_create(&thread_id,NULL, Aircraft_run,(void *) this)!=EOK){
			thread_id=NULL;
		}

	// i don't care about the shared memory as of rn

	//pthread_attr_t attr;
	/* synchronization stuff */
	//pthread_attr_getdetachstate = (&attr ,PTHREAD_CREATE_JOINABLE);
	//pthread_mutexattr_init(&attr);
	//lock count
	//pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	//mutex init
	//pthread_mutex_init(&this->mutex, &attr);
	 //rc = pthread_create(&thread_id, NULL,Aircraft_run,(void *) this)!=EOK


}


void Aircraft::setLocation(Coordinates newPos){
	grid_pos = newPos;
}

void Aircraft::setAltitude( int alt){
	grid_pos.p_z = alt;
	isColliding = false;
}

void Aircraft::setVelocity(Velocity ve){
	velocity = ve;
	isColliding = false;
}

void Aircraft::setCollision(int c){
	isColliding = true;
	//collider = c;
}

void Aircraft::updateCoordinates(){
	grid_pos.p_x += velocity.v_x;
	grid_pos.p_y += velocity.v_y;
	grid_pos.p_z += velocity.v_z;
}

int Aircraft::getId() {
	return p_id;
}

Velocity Aircraft::getVelocity(){
	return velocity;
}
Coordinates Aircraft::getCoordinates(){
	return grid_pos;
}

int Aircraft::calculateXYDistToOtherAircraft(int x, int y){
	//Calculate using a^2 + b^2 = c^2 .
	int distanceXY, diffX, diffY, square;

	diffX = x - this->grid_pos.p_x;
	diffY = y - this->grid_pos.p_y;

	square = pow(diffX,2) + pow(diffY,2);
	distanceXY = (int) sqrt(square); //cast back to INT, certainly some rounding here but we don't care.

	return distanceXY;
}

int Aircraft::calculateZDistToOtherAircraft(int z){
	//TODO
	int distanceZ = abs(z - this->grid_pos.p_z); //Absolute value of the heigh difference between both aircraft

	return distanceZ;
}


//holding pattern basically the function for a circle:
//(x – h)2+ (y – k)2 = r2 (h,k) = coords of middle of the circle
//I'm pretty sure we don't need this. To remove later?

void Aircraft::AircraftPrint(){

	//example of locks
	pthread_mutex_lock(&mutex);
	sleep(10);
	cout << "ID: " << p_id << endl;
	cout << "Coordinates X: " << grid_pos.p_x<< endl;
	cout << "Coordinates Y: " << grid_pos.p_y<< endl;
	cout << "Coordinates Z: " << grid_pos.p_z<< endl;

	cout << "Velocity X: " << velocity.v_x<< endl;
	cout << "Velocity Y: " << velocity.v_y<< endl;
	cout << "Velocity Z: " << velocity.v_z<< endl;

	cout << "Entry Time: " << entryTime<< endl;
	pthread_mutex_unlock(&mutex);
}

/**
 * Aircraft Aircraft::getCollider(){
	return collider;
}
 */

int Aircraft::getEntryTime() {
	return entryTime;
}
