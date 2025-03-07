#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "queue.h"
#define LOOPTIME 1000*1000

typedef struct{
    int inFloor;
    int orderList[N_FLOORS];
    int initialized;
    int onOrderNum;
    int doorsOpen;
    volatile int doorOpenCount;
    int justStopped;
    MotorDirection lastKnownDirection;
} Elevator;

void goToFloor(Elevator* el, int floor, Queue* q);
void wipeOrders(Elevator* el);
void initElevator(Elevator* el, Queue* q);
void stopButton(Elevator* el, Queue* q);
void getnextElement(Queue *q, Elevator* el);
void iGetKnockedDown(Elevator* el);
void ButIGetUpAgain(Elevator* el, Queue* q);

void printQandE(Queue* q, Elevator* el);