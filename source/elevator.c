#include "elevator.h"

void goToFloor(Elevator* el, int floor, Queue* q){
    if (el->inFloor < floor){ //if we're bellow the floor we want to be in
        elevio_motorDirection(DIRN_UP);
    }
    else if (el->inFloor > floor){
        elevio_motorDirection(DIRN_DOWN);
    }
    else if (el -> inFloor == floor){
        if ((el->doorOpenCount*LOOPTIME) >= 3){ //if the doors have been open for 3 seconds
            //commented this out as the queue isn't fully realized yet
            /*if (el->onOrderNum == N_FLOORS-1){ //if we've reached the end of our current queue
                getnextElement(q, el);
            }
            else{
                el -> onOrderNum += 1;
            }*/
            el -> doorOpenCount = 0;
            el -> doorsOpen = 0;
        }
        else{
            el ->doorOpenCount ++;
            el ->doorsOpen = 1;
        }
        elevio_doorOpenLamp(el -> doorsOpen);
        elevio_motorDirection(DIRN_STOP);
    }
        //TODO: extinguish light for floor we were just in (unless it's in another queue-element) (need func to check for all lights??)
    }


void wipeOrders(Elevator* el){
    for (int i = 0; i < N_FLOORS; i++){
        el -> orderList[i] = 0;
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
}