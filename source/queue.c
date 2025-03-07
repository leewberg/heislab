#include "queue.h"

//initializes the queue
void initQ (Queue* q, int dir){ 
    q -> front = -1;
    q -> back = 0;
}

//checks if the queue is empty
int isEmpty(Queue* q){
    return (q->front ==q -> back -1);
}

//checks if the queue is full
int isFull(Queue *q) {
    return (q -> back == MAX_SIZE);
}

//adds an element to the queue
void addFloorToQueue(Queue *q, int floor, int dir){
    if (isFull(q)){
        printf("queue is full, not taking any more orders\n"); //if we get to this point, we've done something wrong
        return;
    }
    if (q -> arr[q->front+1][0][0] == dir){ //and floor not already in queue
        q -> arr[q->front+1][1][N_FLOORS-1] = floor; 
    }
    else if (q -> arr[q->front+2][0][0] == dir){
        q -> arr[q->front+2][1][N_FLOORS-1] = floor;
    }
    else{//must create array if not already dir in queue
        q -> arr[q->back][0][0] = dir;
        q -> arr[q->back][1][0] = floor;
    }
    q -> back ++;
}


//removes everything from the queue
void wipeQueue(Queue* q){
    q -> front = (q -> back -1);
    //LATER: extinguish all lights
    //TODO: nullify all elements?
}
