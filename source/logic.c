#include "logic.h"

void decideOrder(Elevator* el, Queue* q, int f, int b){
    int foundPlace = 0;
    if ((el->inFloor == 0) & (f == 2) & (b == 2)){ //incredibly specific edge-case fix
        elevio_motorDirection(DIRN_UP);
        el->lastKnownDirection = DIRN_UP;
    }
    switch (el -> direction){
    case DIRN_UP:
        if (b == 0 | b == 2){
            if (f > el->inFloor){
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
            if (f < el->inFloor){
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