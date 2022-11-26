#include "Aircraft.h"
#include <iostream>

using namespace std;

Aircraft::Aircraft(int id, Coordinates po, Velocity ve, int entryT) {
	p_id = id;
	location = po;
	velocity = ve;
	entryTime = entryT;
	isColliding = false;
}

Aircraft::Aircraft(){

}

Aircraft::~Aircraft() {
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

/**
 * Aircraft Aircraft::getCollider(){
	return collider;
}
 */

int Aircraft::getEntryTime() {
	return entryTime;
}
