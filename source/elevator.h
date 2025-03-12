#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "queue.h"
#pragma once
#define LOOPTIME 1000*1000
#define RATIO 1000000000/(LOOPTIME)

typedef struct{
    int inFloor;
    int orderList[N_FLOORS];
    int initialized;
    int onOrderNum;
    int doorsOpen;
    volatile int doorOpenCount;
    int justStopped;
    MotorDirection lastKnownDirection;
    MotorDirection direction;
} Elevator;

void goToFloor(Elevator* el, int floor, Queue* q);
void wipeOrders(Elevator* el);
void initElevator(Elevator* el, Queue* q);
void getnextElement(Queue *q, Elevator* el);
void iGetKnockedDown(Elevator* el, Queue* q);
void ButIGetUpAgain(Elevator* el, Queue* q);
void printQandE(Queue* q, Elevator* el);