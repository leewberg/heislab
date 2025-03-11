#include "logic.h"

void decideOrder(Elevator* el, Queue* q, int f, int b){
    int foundPlace = 0;
    switch (el -> direction){
    case DIRN_UP:
        if (b == 0 | b == 2){
            if (f >= el->inFloor){
                el->orderList[f] = f;
                printf("added floor %d to elevator queue\n", f);
                if (f < el->orderList[el->onOrderNum]){
                    el->onOrderNum = f;
                }
                foundPlace = 1;
            }
            else{
                addFloorToQueue(q, f, 1);
                printf("added floor %d to super-queue, direction up\n", f);
                foundPlace = 1;
            }
        }
        else if (b == 1){
            addFloorToQueue(q, f, 0);
            printf("added floor %d to super-queue, direction up\n", f);
            foundPlace = 1;
        }
        break;
    
    case DIRN_DOWN:
        if (b == 1 | b == 2){
            if (f <= el->inFloor){
                el->orderList[N_FLOORS-f-1] = f;
                printf("added floor %d to elevator-queue, direction down\n", f);
                if (f > el->orderList[el->onOrderNum]){
                    el->onOrderNum = N_FLOORS - 1 - f;
                }
                foundPlace = 1;
            }
            else{
                addFloorToQueue(q, f, 1);
                printf("added floor %d to super-queue, direction down\n", f);
                foundPlace = 1;
            }
        }
        else if (b == 0){
            addFloorToQueue(q, f, 1);
            printf("added floor %d to super-queue, direction down\n", f);
            foundPlace = 1;
        }
        break;
    
    default:
        break;
    }
    elevio_buttonLamp(f, b, foundPlace);
    if (foundPlace == 0){
        printf("ERROR, didn't find place for order");
    }
    printQandE(q, el); //DEBUG
}

/*
OLD CODE THAT WE KNOW WORKS
void hoho(Elevator* el, Queue* q, int f, int b){
    int foundPlace = 0;
    
    if ((el->direction == DIRN_UP & b == 0) | (el->direction == DIRN_DOWN & b == 1) | (b == 2)){ //if the outside-button is in the same direction we're going, or if a cab-button is getting pressed
        switch (el->direction){
        case DIRN_UP:
            if (f >= el->inFloor){
                el->orderList[f] = f;
                printf("added floor %d to elevator queue\n", f);
                if (f < el->orderList[el->onOrderNum]){
                    el->onOrderNum = f;
                }
                foundPlace = 1;
            }
            else{
                addFloorToQueue(q, f, 1);
                printf("added floor %d to super-queue, direction up\n", f);
                foundPlace = 1;
            }
            break;
        case DIRN_DOWN:
            if (f <= el->inFloor){
                el->orderList[N_FLOORS-f-1] = f;
                printf("added floor %d to elevator-queue, direction down\n", f);
                if (f > el->orderList[el->onOrderNum]){
                    el->onOrderNum = N_FLOORS - 1 - f;
                }
                foundPlace = 1;
            }
            else{
                addFloorToQueue(q, f, 0);
                printf("added floor %d to super-queue, direction down\n", f);
                foundPlace = 1;
            }
            break;
        default:
            printf("DIDN'T FIND PLACE. direction-based");
            break;
        }
    }
    else{
        //addFloorToQueue(&q, f, ((b+1)%2));
        switch (b){
        case 0:
            addFloorToQueue(q, f, 1);
            printf("added floor %d to super-queue, direction up\n", f);
            foundPlace = 1;
            break;
        case 1:
            addFloorToQueue(q, f, 0);
            printf("added floor %d to super-queue, direction down\n", f);
            foundPlace = 1;
            break;
        default:
            printf("DIDN'T FIND PLACE. non-direction-based");
            break;
        }
    }
    elevio_buttonLamp(f, b, foundPlace);
    if (foundPlace == 0){
        printf("ERROR, didn't find place for order");
    }
    printQandE(q, el); //DEBUG
}*/