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
void * Aircraft::Aircraft_run(void *arg){
	auto air = (Aircraft*) arg;
	//debug
	//air->AircraftPrint();
	air->timer();
	//sleep(5);
	cout << "wow";
	return NULL;
}

//create the the thread outside

void Aircraft::initializeAircraft(){
	int rc;
	if(pthread_create(&thread_id,NULL, Aircraft_run,(void *) this)!=EOK){
			thread_id=NULL;
		}
}



// start listening for messages and reply back
int Aircraft::server() {
   int rcvid;
   // struct containing our msg
   AircraftData msg;
   name_attach_t *attach;

   //AIRCRAFT CHANNEl
   /* Create a local name (/dev/name/local/...) */
   if ((attach = name_attach(NULL, ATTACH_POINT, 0)) == NULL) {
       return EXIT_FAILURE;
   }
   /* Do your MsgReceive's here now with the chid */
   while (1) {
   	   /* Server will block in this call, until a client calls MsgSend to send a message to
   	    * this server through the channel named "myname", which is the name that we set for the channel,
   	    * i.e., the one that we stored at ATTACH_POINT and used in the name_attach call to create the channel. */
	   rcvid = MsgReceive(ch_id, &msg, sizeof(msg), NULL);
	   /* In the above call, the received message will be stored at msg when the server receives a message.
	    * Moreover, rcvid */
       if (rcvid == -1) {/* Error condition, exit */
           break;
       }
       if (rcvid == 0) {/* Pulse received so "aircraft" will fly */
           switch (msg.hdr.code) {
           //start
           case PULSE_START:{
        	   //move the aircraft
        	   updateCoordinates();
        	   break;
           }
           default:
        	   cout << "Plane: " << p_id << " has encountered an error" << endl;
        	   MsgError( rcvid, ENOSYS );
           break;
           }
       }
       //else upon cin for change to aircraft attributes
           else {
        	   switch(msg.cmd_type){
        	   //handle request if required info from plane
        	   case UPDATE: {
        		   AircraftData_response rs;
        		   rs.response_coord = getCoordinates();
        		   rs.response_velo = getVelocity();
        		   rs.response_id = getId();
        		   //EOK no error
        		   //send back the information
        		   MsgReply(rcvid, EOK, &rs, sizeof(rs));
        		   break;
        	   }
        	   //change altitude
        	   case CHANGE_ALTITUDE: {
        		   setAltitude(msg.altitude);
        		    MsgReply(rcvid, EOK, NULL, 0 );
        		    break;
        	   }
        	   //change velocity
        	   case CHANGE_VELOCITY: {
         		   setVelocity(msg.velo);
         		   MsgReply( rcvid, EOK, NULL, 0 );
         		  break;
        	   }
        	   //print
        	   case PRINT: {
        		   AircraftPrint();
        		   MsgReply( rcvid, EOK, NULL, 0 );
        		   break;
        	   }
               default:
               	   cout << "Plane: " << p_id << " has encountered an error" << endl;
               	   MsgError( rcvid, ENOSYS );
                  break;
        	   }
           }
   }


   //remove name from the space
   name_detach(attach, 0);
   return EXIT_SUCCESS;
}


//attach timer to airplane channel and start server()
int Aircraft::timer(){
    my_data_t msg;
    // note: we create a connection back to our own channel using (ch_id)
    // use separate class for timer functionality?
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
	SIGEV_PULSE_INIT(&sig_event, connection_id, SIGEV_PULSE_PRIO_INHERIT, 1, 0);
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
    cout << "aircraft: " << p_id << " has started the server" << endl;
    server();
    return EXIT_SUCCESS;
}


//start communication
int Aircraft::client(int ch_id){
	AircraftData msg;
	//connect to arg's channel
	//_NTO_SIDE_CHANNEL should always be used to ignore index
	int connection_id = ConnectAttach(0,0,ch_id,_NTO_SIDE_CHANNEL,0);
	for (int i = 0; i < 15; i++) {

		/**
		 *
		 *
		 * 		msg.command = 1;
		PlanePositionResponse res;
		MsgSend(connection_id, &msg, sizeof(msg), &res, sizeof(res));
		std::cout << "Position: <" << res.currentPosition.x << ','
				<< res.currentPosition.y << ',' << res.currentPosition.z
				<< ">, ";
		std::cout << "Velocity: <" << res.currentVelocity.x << ','
				<< res.currentVelocity.y << ',' << res.currentVelocity.z << ">";
		std::cout << std::endl;

		sleepUntil = now() + 1000 * 1000 * 1000;
		while (now() < sleepUntil)
			;
		 *
		 */

	}

}

void Aircraft::setLocation(Coordinates newPos){
	grid_pos = newPos;
}

void Aircraft::setAltitude( int alt){
	grid_pos.p_z = alt;
	isColliding = false;
}

void Aircraft::setVelocity(Velocity ve){
	velocity.v_x = ve.v_x;
	velocity.v_y = ve.v_y;
	velocity.v_z= ve.v_z;
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
