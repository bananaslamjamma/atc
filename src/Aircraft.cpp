#include "Aircraft.h"
#include <iostream>

using namespace std;

//make a copy of this constructor for a threaded version
Aircraft::Aircraft(int id, Coordinates po, Velocity ve, int entryT) {
	p_id = id;
	location = po;
	velocity = ve;
	entryTime = entryT;
	isColliding = false;

	grid_pos.p_x = location.p_x;
	grid_pos.p_y = location.p_y;
	grid_pos.p_z = location.p_z;
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

	init_Aircraft();
}


void Aircraft::init_Aircraft(){
	int rc;


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

void *dummy(int arg){

	sleep(5);
	cout << "I'm a dummy";
	return NULL;
}

Aircraft::~Aircraft() {
	thread_id = NULL;

}

void * Aircraft_run(void *arg){
	Aircraft& air = *(Aircraft*) arg;

	//pthread_join(&thread_id, NULL);
	sleep(5);
	cout << "waking up";
	//pthread_exit(NULL);
	return NULL;
}

void Aircraft::setLocation(Coordinates newPos){
	location = newPos;
}

void Aircraft::setAltitude( int alt){
	location.p_z = alt;
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
	location.p_x += velocity.v_x;
	location.p_y += velocity.v_y;
	location.p_z += velocity.v_z;
}

int Aircraft::getId() {
	return p_id;
}

Velocity Aircraft::getVelocity(){
	return velocity;
}
Coordinates Aircraft::getCoordinates(){
	return location;
}


//holding pattern basically the function for a circle:
//(x – h)2+ (y – k)2 = r2 (h,k) = coords of middle of the circle

void Aircraft::AircraftPrint(){
	cout << "ID: " << p_id << endl;
	cout << "Coordinates X: " << grid_pos.p_x<< endl;
	cout << "Coordinates Y: " << grid_pos.p_y<< endl;
	cout << "Coordinates Z: " << grid_pos.p_z<< endl;

	cout << "Velocity X: " << velocity.v_x<< endl;
	cout << "Velocity Y: " << velocity.v_y<< endl;
	cout << "Velocity Z: " << velocity.v_z<< endl;

	cout << "Entry Time: " << entryTime<< endl;
}

/**
 * Aircraft Aircraft::getCollider(){
	return collider;
}
 */

int Aircraft::getEntryTime() {
	return entryTime;
}
