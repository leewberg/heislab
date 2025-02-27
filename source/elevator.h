#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "queue.h"

typedef struct{
    int inFloor;
    int orderList[N_FLOORS];
    int initialized;
    int onOrderNum;
    int doorsOpen;
} Elevator;

void goToFloor(Elevator* el, int floor);
//use elevio motor direction to get it to go in the apropriate direction, and we send it to stop once it reaches the floor we want it to be on

void getNextOrder(Elevator* el);
void wipeOrders(Elevator* el);
void initElevator(Elevator* el);
void stopButton(Elevator* el, Queue* q);
void getnextElement(Queue *q, Elevator* el);

//remove these?
void checkOrders();
void checkObstruction();
void drive();