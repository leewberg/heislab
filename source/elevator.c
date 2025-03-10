#include "elevator.h"

void goToFloor(Elevator* el, int floor, Queue* q){
    if (floor == -1){ //if the current order is invalids
        elevio_doorOpenLamp(0);
        if (el->onOrderNum == N_FLOORS -1){
            getnextElement(q, el);
        }
        else{
            el->onOrderNum += 1;
        }
        return;
    }
    
    else{if (el->inFloor < floor){ //if we're bellow the floor we want to be in
        elevio_motorDirection(DIRN_UP);
        el -> lastKnownDirection = DIRN_UP; //saving these in case we stop between floors
    }

    else if (el->inFloor > floor){
        elevio_motorDirection(DIRN_DOWN);
        el -> lastKnownDirection = DIRN_DOWN;
    }

    else if (el -> inFloor == floor){ //once we've reached our floor
        if ((el->doorOpenCount) >= 3*10){ //if the doors have been open for 3 seconds
            //real: doorOpenCount >= 3*LOOPTIME
            printf("order completed\n");
            if (el->orderList[el->onOrderNum] == floor | el-> lastKnownDirection == DIRN_UP){ //we have been going upwards
                elevio_buttonLamp(floor, 0, 0);
            }
            if (el->orderList[N_FLOORS - 1 - floor] == floor | el->lastKnownDirection == DIRN_DOWN){ //we have been going downwards
                elevio_buttonLamp(floor, 1, 0);
            }
            elevio_buttonLamp(floor, 2, 0);

            if (el->onOrderNum == N_FLOORS-1){ //if we've reached the end of our current queue
                getnextElement(q, el);
                printf("getting next order from queue\n");
                el -> doorOpenCount = 0;
                el -> doorsOpen = 0;
            }
            else{
                printf("increasing place in elevator order list \n");
                el -> onOrderNum += 1;
                el -> doorOpenCount = 0;
                el -> doorsOpen = 0;
            }
            el->orderList[el->onOrderNum] = -1;
        }
        else{
            el ->doorOpenCount ++;
            el ->doorsOpen = 1;
        }
        elevio_doorOpenLamp(el -> doorsOpen);
        elevio_motorDirection(DIRN_STOP);}
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
    el->lastKnownDirection = DIRN_UP;
    for (int i = 0; i < N_FLOORS; i++){
        el -> orderList[i] = -1;
    }
    el -> doorOpenCount = 0;
    el -> initialized = 1;
    elevio_doorOpenLamp(0);
}


//returns the element at the start of the queue. also removes said element from the queue by moving the front up one value.
void getnextElement(Queue *q, Elevator* el){
    el -> onOrderNum = 0; //start the order-queue from scratch
    if (isEmpty(q)){ //FEIL HER?
        //can be used to stop the elevator when no further orders
        elevio_motorDirection(DIRN_STOP);
        printf("no orders, on standby\n");
        //in theory the doors will close on their own as long as they've been open dor 3 seconds and we don't have any new orders. if not, here is the place we will close the doors
        return;
    }
    else{
        for (int i = 0; i<N_FLOORS; i++){
            int index = (q->front+1)%MAX_SIZE;
            el -> orderList[i] = q->arr[index][1][i];
            q->arr[index][1][i] = -1; //nullifies the previous element, getting it ready for the next batch of orders
        }
        q -> front += 1;
        q -> back -= 1;
    }
}

void iGetKnockedDown(Elevator* el, Queue* q){
    elevio_stopLamp(1);
    elevio_motorDirection(DIRN_STOP);
    wipeOrders(el);
    wipeQueue(q);
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
    if (el->inFloor == elevio_floorSensor()){ //once in a floor, keep doors open
        if (el -> doorOpenCount >=3*10){
            el-> doorOpenCount = 0;
            el->justStopped = 0;
            elevio_stopLamp(0);
            elevio_doorOpenLamp(0);
        }
        else{
            elevio_motorDirection(DIRN_STOP);
            elevio_doorOpenLamp(1);
            el -> doorOpenCount += 1;
        }
    }
}

void printQandE(Queue* q, Elevator* el){
    printf("Queue: \n");
    for (int i = 0; i < MAX_SIZE; i++){
        printf("direction %d\n",i);
        for (int j = 0; j < N_FLOORS; j++){
            printf("%d \n", q ->arr[i][1][j]);
        }
    }

    printf("Elevator Queue: \ngoing %d\n", el->lastKnownDirection);
    for (int i = 0; i < N_FLOORS; i++){
        printf("%d \n", el->orderList[i]);
    }

}