#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator.h"

//ISSUE: elevator queue isn't wiped at stop


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

            /*if(floor == 0){ //if we're at the bottom, change directions
                elevio_motorDirection(DIRN_UP);
                el.lastKnownDirection = DIRN_UP;
            }

            if(floor == N_FLOORS-1){ //if we're at the top, change directions
                elevio_motorDirection(DIRN_DOWN);
                el.lastKnownDirection = DIRN_DOWN;
            }*/

            goToFloor(&el, el.orderList[el.onOrderNum], &q); 
            //sets elevator to go to the floor of its next queue-element

            for(int f = 0; f < N_FLOORS; f++){ //f: floor
                for(int b = 0; b < N_BUTTONS; b++){ //b: button on each floor
                    int btnPressed = elevio_callButton(f, b); //bool that tells us if button is pressed

                    if (btnPressed){
                        elevio_buttonLamp(f, b, 1);
                        //TODO: compress to cleaner code
                        if ((el.lastKnownDirection == DIRN_UP & b == 0) | (el.lastKnownDirection == DIRN_DOWN & b == 1) | b == 2){ //if the outside-button is in the same direction we're going, or if a cab-button is getting pressed
                            switch (el.lastKnownDirection){
                            case DIRN_UP:
                                if (f > el.inFloor){
                                    el.orderList[f] = f;
                                    printf("added floor %d to elevator queue\n", f);
                                    if (el.orderList[el.onOrderNum] == -1){
                                        el.onOrderNum = f;
                                    }
                                }
                                else{
                                    addFloorToQueue(&q, f, 1);
                                    printf("added floor %d to super-queue, direction up\n", f);
                                }
                                break;
                            case DIRN_DOWN:
                                if (f < el.inFloor){
                                    el.orderList[N_FLOORS-f-1] = f;
                                    printf("added floor %d to elevator-queue, direction down\n", f);
                                    if (el.orderList[el.onOrderNum] == -1){
                                        el.onOrderNum = N_FLOORS -1 -f;
                                    }
                                }
                                else{
                                    addFloorToQueue(&q, f, 0);
                                    printf("added floor %d to super-queue, direction down\n", f);
                                }
                                break;
                            default:
                                addFloorToQueue(&q, f, 1);
                                break;
                            }
                        }
                        else{
                            //addFloorToQueue(&q, f, ((b+1)%2));
                            switch (b){
                            case 0:
                                addFloorToQueue(&q, f, 1);
                                printf("added floor %d to super-queue, direction up\n", f);
                                break;
                            case 1:
                                addFloorToQueue(&q, f, 0);
                                printf("added floor %d to super-queue, direction down\n", f);
                                break;
                            default:
                                addFloorToQueue(&q, f, 1);
                                break;
                            }
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
