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
void lightIndicator();
void getNextOrder();
void wipeOrders();
void initElevator();
void standStill();
void stopButton();
void checkOrders();
void checkObstruction();
void drive();