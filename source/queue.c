#include "queue.h"

//initializes the queue
void initQ (Queue* q){ 
    q -> front = -1;
    q -> back = 0;
    //initialize q w/ all invalid floors
    for (int i = 0; i < MAX_SIZE; i ++){
        q -> arr[i][0][0] = i;
        //have then kind of "rigid" queue elements where we can only truly modify the element order
        //this means that index 0 carries the "down" orders, and 1 carries the "up" orders
        for (int j = 0; j < N_FLOORS; j++){
            q->arr[i][1][j] = -1;
        }
    }
}

//adds an element to the queue
void addFloorToQueue(Queue *q, int floor, int dir){
    switch (dir){
        case 0: //going down
            q->arr[0][1][N_FLOORS - 1 - floor] = floor;
            q-> back ++;
            printf("added %d to queue, going down\n", floor);
            break;
        case 1:
            q->arr[1][1][floor] = floor;
            q->back++;
            printf("added %d to queue, going up\n", floor);
            break;
        default:
            printf("cannot add element to queue. didn't find place to put it\n");
            break;
        }
}


//removes everything from the queue
void wipeQueue(Queue* q){
    q -> front = -1;
    extLightIndicators(); // extinguish all lights
    for (int f = 0; f < N_FLOORS; f++) { // nullify all elements in the queue (set to -1) 
        q -> arr[0][1][f] = -1;
        q -> arr[1][1][f] = -1;
    }
}

