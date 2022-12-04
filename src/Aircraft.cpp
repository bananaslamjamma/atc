#include "Aircraft.h"
#include "math.h"
#include <time.h>
#include <iostream>

using namespace std;


Aircraft::Aircraft(int id, Coordinates po, Velocity ve, int entryT) {
	p_id = id;
	grid_pos = po;
	velocity = ve;
	entryTime = entryT;
	hasArrived = false;
	initializeAircraft();
}

Aircraft::Aircraft(){

}

//debugging
Aircraft::Aircraft(int id){
	p_id = id;
	grid_pos.p_x = 1;
	grid_pos.p_y = 0;
	grid_pos.p_z = 1;
	velocity.v_x = 1;
	velocity.v_y = 1;
	velocity.v_z = 1;
	entryTime = 5;
	hasArrived =  false;
	initializeAircraft();
}

Aircraft::~Aircraft() {
	pthread_mutex_destroy( &mutex );
	thread_id = NULL;

}

// function that pthread_create() calls
void * Aircraft::Aircraft_run(void *arg){
	auto air = (Aircraft*) arg;
	//debug
	//air->AircraftPrint();
	air->timer();
	cout << "task completed";
	return NULL;
}

//called upon constructor call
void Aircraft::initializeAircraft(){
	if(pthread_create(&thread_id,NULL, Aircraft_run,(void *) this)!=EOK){
			thread_id=NULL;
		}
}

// start listening for messages and reply back
int Aircraft::server() {
   int rcvid;
   // struct containing our msg
   AircraftData msg;

   //don't need a local attach name
   while (1) {
	   cout << "entered server loop" << endl;
   	   /* server will block until message received **/
	   rcvid = MsgReceive(ch_id, &msg, sizeof(msg), NULL);
	   /* received message will be stored in msg. */
	   /* Error condition, exit */
       if (rcvid == -1) {
    	   cout << "error" << endl;
           break;
       }
       if (rcvid == 0) {/* Pulse received so "aircraft" will fly */
    	   //cout << "pulse received" << endl;
    	   //no other pulse codes
           switch (msg.hdr.code) {
           default:
               	   //start
            	   //move the aircraft
            	   //cout << "being called" << endl;
            	   updateCoordinates();
           break;
           }
       }
       //else upon cin for change to aircraft attributes, rcvid>0
           else {
        	   switch(msg.cmd_type){
        	   //handle request if required info from plane
        	   case PING:
        		   cout << "being pinged" << endl;
        		   AircraftData_response rs;
        		   rs.response_coord = getCoordinates();
        		   rs.response_velo = getVelocity();
        		   rs.response_id = getId();
        		   //EOK no error
        		   //send back the information
        		   MsgReply(rcvid, EOK, &rs, sizeof(rs));
        		   break;

        	   //change altitude
        	   case CHANGE_ALTITUDE:
        		   setAltitude(msg.altitude);
        		    MsgReply(rcvid, EOK, NULL, 0 );
        		    break;

        	   //change velocity
        	   case CHANGE_VELOCITY:
         		   setVelocity(msg.velo);
         		   MsgReply( rcvid, EOK, NULL, 0 );
         		  break;

        	   //exit
        	   case EXIT:
        		   MsgReply( rcvid, EOK, NULL, 0 );
        		   //close the connection, stop listening
        		   return EXIT_SUCCESS;
               default:
               	   cout << "Aircraft: " << p_id << " has encountered an error" << endl;
               	   MsgError( rcvid, ENOSYS );
                  break;
        	   }
           }
   }
   return EXIT_SUCCESS;
}


//attach timer to airplane channel and start server()
int Aircraft::timer(){
    my_data_t msg;
    // note: we create a connection back to our own channel using (ch_id)
    int connection_id;
	ch_id = ChannelCreate(0);
	connection_id = ConnectAttach(0,0,ch_id,0,0);
	if(connection_id == -1){
		std::cerr << "Timer, Failed to Attach error : " << errno << "\n";
	}
	//define clock attributes
	struct sigevent sig_event;
	//delay, reload
	struct itimerspec timer_config;
	//timer
	timer_t mono_timer;
	//timer pulse every 1 second
	SIGEV_PULSE_INIT(&sig_event, connection_id, SIGEV_PULSE_PRIO_INHERIT, PULSE_CODE, 0);
	//debugcout << "TIMER pulse initiated" << endl;

	//create a timer
	//bind it to the event
	if (timer_create(CLOCK_MONOTONIC, &sig_event, &mono_timer) == -1){
		std::cerr << "Timer, Init error : " << errno << "\n";
	}

	// delay should be arrivalTime of each task(aircraft)
    timer_config.it_value.tv_sec = getEntryTime();
    timer_config.it_value.tv_nsec = 0;
    timer_config.it_interval.tv_sec = 1;
    timer_config.it_interval.tv_nsec = 0;

    // start timer
    cout << "aircraft: " << p_id << " has started their timer" << endl;
    timer_settime (mono_timer, 0, &timer_config, NULL);

    //task has arrived, now wait for messages
    //cout << "aircraft: " << p_id << " has started the server" << endl;
    server();
    return EXIT_SUCCESS;
}


//start communication
int Aircraft::ping(int ch_id){
	AircraftData msg;
	AircraftData_response reply;
	//connect to arg's channel
	//_NTO_SIDE_CHANNEL should always be used to ignore index
	int connection_id = ConnectAttach(0,0,ch_id,_NTO_SIDE_CHANNEL,0);
	msg.cmd_type = PING;
	//send a message 20 times to simulate runtime
	for (int i = 0; i < 20; i++) {
		MsgSend(connection_id, &msg, sizeof(msg), &reply, sizeof(reply));
		cout << "Aircraft ID: " << p_id << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "Coordinates : <" << grid_pos.p_x << ", " << grid_pos.p_y<<  ", " << grid_pos.p_z << " >" <<  endl;
		cout << "--------------------------------------------------" << endl;
		cout << "Velocity : <" << velocity.v_x << ", " << velocity.v_y<<  ", " << velocity.v_z << " >" <<  endl;
		cout << "--------------------------------------------------" << endl;
		cout << "Entry Time: " << entryTime<< endl;
		//wait for 1s
		sleep(1);
	}
	//send a message to close the connection
	msg.cmd_type = EXIT;
	MsgSend(connection_id, &msg, sizeof(msg), NULL, 0);
}

void Aircraft::setLocation(Coordinates newPos){
	grid_pos = newPos;
}

void Aircraft::setAltitude( int alt){
	grid_pos.p_z = alt;
}

void Aircraft::setVelocity(Velocity ve){
	velocity.v_x = ve.v_x;
	velocity.v_y = ve.v_y;
	velocity.v_z= ve.v_z;

}

void Aircraft::setArrival(){
	hasArrived = true;
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

int Aircraft::getEntryTime() {
	return entryTime;
}
