#include "elevator.h"

void goToFloor(Elevator* el, int floor, Queue* q){
    if (el->inFloor < floor){ //if we're bellow the floor we want to be in
        elevio_motorDirection(DIRN_UP);
        el -> lastKnownDirection = DIRN_UP; //saving these in case we stop between floors
    }

    else if (el->inFloor > floor){
        elevio_motorDirection(DIRN_DOWN);
        el -> lastKnownDirection = DIRN_DOWN;
    }

    else if (el -> inFloor == floor){ //once we've reached our floor
        if ((el->doorOpenCount*LOOPTIME) >= 3*LOOPTIME){ //if the doors have been open for 3 seconds
            //commented this out as the queue isn't fully realized yet
            /*if (el->onOrderNum == N_FLOORS-1){ //if we've reached the end of our current queue
                getnextElement(q, el);
            }
            else{
                el -> onOrderNum += 1;
            }*/
            el -> doorOpenCount = 0;
            el -> doorsOpen = 0;
            if (el-> lastKnownDirection == DIRN_DOWN){ //if we were going down, and the order is completed, we extinguish the lights for the call-button for down on that floor and the cab-light for that floor
                elevio_buttonLamp(floor, 1, 0);
                elevio_buttonLamp(floor, 2, 0);
            }
            else if (el->lastKnownDirection == DIRN_UP){
                elevio_buttonLamp(floor, 0, 0);
                elevio_buttonLamp(floor, 2, 0);
            }
        }
        else{
            el ->doorOpenCount ++;
            el ->doorsOpen = 1;
        }
        elevio_doorOpenLamp(el -> doorsOpen);
        elevio_motorDirection(DIRN_STOP);
    }
}


void wipeOrders(Elevator* el){
    for (int i = 0; i < N_FLOORS; i++){
        el -> orderList[i] = -1;
    } //nullifies all orders
}


void initElevator(Elevator* el, Queue* q){
    el -> initialized = 0;
    el -> onOrderNum = 0;
    el -> doorsOpen = 0;
    el -> justStopped = 0;
    el -> inFloor = elevio_floorSensor();
    while (el->inFloor != 0){
        int floor = elevio_floorSensor();
        if (floor != -1){
            el -> inFloor = floor;
        }
        goToFloor(el, 0, q);
    }
    el -> doorOpenCount = 0;
    el -> initialized = 1;
    elevio_doorOpenLamp(0);
}

void stopButton(Elevator* el, Queue* q){
    wipeOrders(el);
    wipeQueue(q);
    elevio_motorDirection(DIRN_STOP);
    elevio_stopLamp(1);
    wipeQueue(q);
}

//returns the element at the start of the queue. also removes said element from the queue by moving the front up one value.
void getnextElement(Queue *q, Elevator* el){
    el -> onOrderNum = 0; //start the order-queue from scratch
    if (isEmpty(q)){
        //can be used to stop the elevator when no further orders
        return;
    }
    for (int i = 0; i<N_FLOORS; i++){
        el -> orderList[i] = q->arr[q->front+1][1][i];
    }
    q -> front += 1;
    q -> back -= 1;
}

void iGetKnockedDown(Elevator* el){
    elevio_stopLamp(1);
    elevio_motorDirection(DIRN_STOP);
    el -> justStopped = 1;
    if (elevio_floorSensor() != -1){
        elevio_doorOpenLamp(1);
    }

}

void ButIGetUpAgain(Elevator* el, Queue* q){
    if (elevio_floorSensor() == -1){//if we're between two floors
        el -> doorOpenCount = 0;
        if (el->lastKnownDirection == DIRN_DOWN){ //if we were previously going down, we have to go up to return to our previous floor
            elevio_motorDirection(DIRN_UP);
        }
        else{
            elevio_motorDirection(DIRN_DOWN);
        }
    }
    if (el->inFloor == elevio_floorSensor()){
        if (el -> doorOpenCount*LOOPTIME >=3){
            el-> doorOpenCount = 0;
            el->justStopped = 0;
            elevio_stopLamp(0);
            elevio_doorOpenLamp(0);
        }
        else{
            elevio_doorOpenLamp(1);
            el -> doorOpenCount += 1;
        }
    }
}