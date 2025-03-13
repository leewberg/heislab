#include "elevator.h"

void goToFloor(Elevator* el, int floor, Queue* q){
    if (floor == -1){ //if the current order is invalids
        elevio_doorOpenLamp(0);
        elevio_motorDirection(DIRN_STOP);
        if (el->onOrderNum == N_FLOORS -1){
            getnextElement(q, el);
        }
        else{
            el->onOrderNum += 1;
        }
        return;
    }
    
    else {
        if (el->inFloor < floor){ //if we're bellow the floor we want to be in
            elevio_motorDirection(DIRN_UP);
        }
    
        else if (el->inFloor > floor){
            elevio_motorDirection(DIRN_DOWN);
        }

        else if ((el -> inFloor == floor) & (elevio_floorSensor() != -1)){ //once we've reached our floor
            if ((el->doorOpenCount) >= RATIO/50){ //if the doors have been open for 3 seconds. add room for some extra nanoseconds outside of the looptime just so the program itself has time to run
                
                if (el->orderList[N_FLOORS - 1 - floor] == floor | el->direction == DIRN_DOWN){ //we have been going downwards
                    elevio_buttonLamp(floor, 1, 0);
                }
                if (el->orderList[el->onOrderNum] == floor | el-> direction == DIRN_UP){ //we have been going upwards
                    elevio_buttonLamp(floor, 0, 0);
                }
                elevio_buttonLamp(floor, 2, 0);

                if (el->onOrderNum == N_FLOORS-1){ //if we've reached the end of our current queue
                    getnextElement(q, el);
                    el -> doorOpenCount = 0;
                    el -> doorsOpen = 0;
                }
                else{
                    el -> onOrderNum += 1;
                    el -> doorOpenCount = 0;
                    el -> doorsOpen = 0;
                }
            }
            else{
                el ->doorOpenCount ++;
                el ->doorsOpen = 1;
            }
            elevio_doorOpenLamp(el -> doorsOpen);
            elevio_motorDirection(DIRN_STOP);
        }
        else{//if per example between floors after a stop and cab button is pressed for floor we were in
            elevio_motorDirection(DIRN_UP);
        }
    }
}


void wipeOrders(Elevator* el){
    for (int i = 0; i < N_FLOORS; i++){
        el -> orderList[i] = -1;
    }
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
    el->direction = DIRN_UP;
    for (int i = 0; i < N_FLOORS; i++){
        el -> orderList[i] = -1;
    }
    el -> doorOpenCount = 0;
    el -> initialized = 1;
    elevio_doorOpenLamp(0);
}



void getnextElement(Queue *q, Elevator* el){
    el -> onOrderNum = 0; 
    int index = (q->front+1)%MAX_SIZE;
    for (int i = 0; i<N_FLOORS; i++){
        el -> orderList[i] = q->arr[index][1][i];
        q->arr[index][1][i] = -1; //nullifies the previous element, getting it ready for the next batch of orders
    }
    if (q->arr[index][0][0]==0){
        el -> direction = DIRN_DOWN;
    }
    else{
        el -> direction = DIRN_UP;
    }
    q -> front += 1;
}


void stopButton(Elevator* el, Queue* q){
    elevio_stopLamp(1);
    elevio_motorDirection(DIRN_STOP);
    wipeOrders(el);
    wipeQueue(q);
    el -> justStopped = 1;
    if (elevio_floorSensor() != -1){
        elevio_doorOpenLamp(1);
        el -> doorOpenCount = 0;
    }
    else{
        el -> doorOpenCount = (RATIO/10)-50;
    }

}


void returnAfterStop(Elevator* el, Queue* q){
    if (el->inFloor == elevio_floorSensor()){ //if in a floor, keep doors open
        elevio_doorOpenLamp(1);
        if (elevio_obstruction()){ //still need to check for obstructions
            el -> doorOpenCount = 0;
        }
    }
    if (el -> doorOpenCount >= RATIO/25){ //if the doors have been open for 3s
        el-> doorOpenCount = 0;
        el->justStopped = 0;
        elevio_stopLamp(0);
        elevio_doorOpenLamp(0);
    }
    else{
        elevio_motorDirection(DIRN_STOP);
        el -> doorOpenCount += 1;
    }
}


void printQandE(Queue* q, Elevator* el){
    printf("Queue: \n");
    for (int i = 0; i < MAX_SIZE; i++){
        printf("direction %d:\n",i);
        for (int j = 0; j < N_FLOORS; j++){
            printf("%d \n", q ->arr[i][1][j]);
        }
    }

    printf("Elevator Queue, going %d:\n", el->direction);
    for (int i = 0; i < N_FLOORS; i++){
        printf("%d \n", el->orderList[i]);
    }

}