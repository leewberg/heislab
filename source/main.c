#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator.h"

//ISSUE: elevator skips floors


int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_UP);
    extLightIndicators();
    Queue q;
    initQ(&q);
    Elevator el;
    initElevator(&el, &q);


    while(1){
        if (elevio_stopButton()){
            iGetKnockedDown(&el, &q);
        }
        else if (el.justStopped){
            ButIGetUpAgain(&el, &q);
        }
        else{
            int floor = elevio_floorSensor(); //sets floor. returns -1 when not in a floor
            if (floor!= -1){
                el.inFloor = floor; //only sets floor when not between floors
                elevio_floorIndicator(floor);
            }

            goToFloor(&el, el.orderList[el.onOrderNum], &q); 
            //sets elevator to go to the floor of its next queue-element

            for(int f = 0; f < N_FLOORS; f++){ //f: floor
                for(int b = 0; b < N_BUTTONS; b++){ //b: button on each floor
                    int btnPressed = elevio_callButton(f, b); //bool that tells us if button is pressed

                    if (btnPressed){
                        int foundPlace = 0;
                        //TODO: compress to cleaner code
                        if ((el.direction == DIRN_UP & b == 0) | (el.direction == DIRN_DOWN & b == 1)){ //if the outside-button is in the same direction we're going, or if a cab-button is getting pressed
                            switch (el.direction){
                            case DIRN_UP:
                                if (f >= el.inFloor){
                                    el.orderList[f] = f;
                                    printf("added floor %d to elevator queue\n", f);
                                    if (el.orderList[el.onOrderNum] == -1){
                                        el.onOrderNum = f;
                                        printf("changed order number\n");
                                    }
                                    foundPlace = 1;
                                }
                                else{
                                    addFloorToQueue(&q, f, 1);
                                    printf("added floor %d to super-queue, direction up\n", f);
                                    foundPlace = 1;
                                }
                                break;
                            case DIRN_DOWN:
                                if (f <= el.inFloor){
                                    el.orderList[N_FLOORS-f-1] = f;
                                    printf("added floor %d to elevator-queue, direction down\n", f);
                                    if (el.orderList[el.onOrderNum] == -1){
                                        el.onOrderNum = N_FLOORS -1 -f;
                                    }
                                    foundPlace = 1;
                                }
                                else{
                                    addFloorToQueue(&q, f, 0);
                                    printf("added floor %d to super-queue, direction down\n", f);
                                    foundPlace = 1;
                                }
                                break;
                            default:
                                printf("DIDN'T FIND PLACE. direction-based");
                                /*(addFloorToQueue(&q, f, 1);
                                    foundPlace = 1;)*/
                                break;
                            }
                        }
                        else if (b == 2){
                            if ((el.direction == DIRN_UP) & (f >= el.inFloor)){
                                el.orderList[f] = f;
                                foundPlace = 1;
                            }
                            else if ((el.direction == DIRN_DOWN) & (f <= el.inFloor)){
                                el.orderList[N_FLOORS-1-f] = f;
                                foundPlace = 1;
                            }
                            else if (el.direction == DIRN_DOWN){
                                addFloorToQueue(&q, f, 0);
                                foundPlace = 1;
                            }
                            else if (el.direction == DIRN_UP){
                                addFloorToQueue(&q, f, 1);
                                foundPlace = 1;
                            }
                        }
                        else{
                            //addFloorToQueue(&q, f, ((b+1)%2));
                            switch (b){
                            case 0:
                                addFloorToQueue(&q, f, 1);
                                printf("added floor %d to super-queue, direction up\n", f);
                                foundPlace = 1;
                                break;
                            case 1:
                                addFloorToQueue(&q, f, 0);
                                printf("added floor %d to super-queue, direction down\n", f);
                                foundPlace = 1;
                                break;
                            default:
                                /*addFloorToQueue(&q, f, 1);
                                foundPlace = 1;*/
                                printf("DIDN'T FIND PLACE. non-direction-based");
                                break;
                            }
                        }
                        elevio_buttonLamp(f, b, foundPlace);
                        if (foundPlace == 0){
                            printf("ERROR, didn't find place for order");
                        }
                        printQandE(&q, &el); //DEBUG
                    }
                }
            }



            if(elevio_obstruction()){ //checks if we have an obstruction
                elevio_stopLamp(1);
                el.doorOpenCount = 0;
            } 
            else {
                elevio_stopLamp(0);
            }

        }
        
        nanosleep(&(struct timespec){0, LOOPTIME}, NULL); //can use this to keep track of how long doors have been open
    }

    return 0;
}
