#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "lights.h"
#define MAX_SIZE 2
#pragma once



typedef struct{
    int arr[MAX_SIZE][2][N_FLOORS];
    int front;
}Queue;


void initQ (Queue* q);
void addFloorToQueue(Queue *q, int floor, int dir);
void wipeQueue(Queue* q);


/*
example Queue:
queue q = {
    {{0, 0, 0, 0}, {3, 2, 1, 0}}, //this is an order where we go down from level 4 and stop by every floor
    {{1, 0, 0, 0}, {0, 1, -1, 3}} //this is an order where we go up from level 1 and stop in every floor except the third
}


if the first element is 0, the elevator is supposed to go down on that run
if the first element is 1, the elevator is supposed to go up
*/