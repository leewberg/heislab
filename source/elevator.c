#include "elevator.h"

void goToFloor(Elevator* el, int floor){
    if (el->inFloor < floor){ //if we're bellow the floor we want to be in
        elevio_motorDirection(DIRN_UP);
    }
    else if (el->inFloor > floor){
        elevio_motorDirection(DIRN_DOWN);
    }
    else{
        elevio_motorDirection(DIRN_STOP);
        if (el->onOrderNum == N_FLOORS-1){ //if we've reached the end of our current queue
            getNextOrder(el);
        }
        else{
            el -> onOrderNum += 1;
        }
    }
}

void getNextOrder(Elevator* el){
    el -> onOrderNum = 0; //start the order-queue from scratch
}
void wipeOrders();
void initElevator(Elevator* el){
    el -> initialized = 0;
    el -> onOrderNum = 0;
    el -> doorsOpen = 0;
    while (el->inFloor != 0){
        goToFloor(el, 0);
    }
    el -> initialized = 1;
}

void stopButton();
void checkOrders();
void checkObstruction();
void drive();