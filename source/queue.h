#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#define MAX_SIZE 2



typedef struct{
    int arr[MAX_SIZE][2][N_FLOORS];
    int back;
    int front;
}Queue;

//for child struct
void initQ (Queue* q, int dir);
int isFull(Queue *q);
int isEmpty(Queue* q);
void addFloorToQueue(Queue *q, int floor, int dir);
void printQueue(Queue* q);
void removeFromQueue(Queue *q);
int getnextElement(Queue *q);
void wipeQueue(Queue* q);

/*
example Queue:
queue q = {
    {{0, 0, 0, 0}, {4, 3, 2, 1}}, //this is an order where we go down from level 4
    {{1, 0, 0, 0}, {2, 3, 4, 0}} //this is an order where we go up from level 1
}

must then ignore 0 when sorting the orders. alternatively: ignore 0 when executing the orders


if the first element is 0, the elevator is supposed to go down on that run
if the first element is 1, the elevator is supposed to go up
*/