#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

struct Elevator{
    int inFloor;
    int orderList;
    bool door_open;
    bool drivingDirection;
    bool initialized;
};

void goToFloor();
//use elevio motor direction to get it to go in the apropriate direction, and we send it to stop once it reaches the floor we want it to be on

void lightIndicator(); //IRRELEVANT
void getNextOrder();
void wipeOrders();
void initElevator();
void standStill();
void stopButton();
void checkOrders();
void checkObstruction();
void drive();