#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator.h"
#include "logic.h"

int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    extLightIndicators();
    Queue q;
    initQ(&q);
    Elevator el;
    initElevator(&el, &q);
    elevio_motorDirection(DIRN_DOWN);


    while(1){
        if (elevio_stopButton()){
            stopButton(&el, &q);
        }
        else if (el.justStopped){
            returnAfterStop(&el, &q);
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
                        decideOrder(&el, &q, f, b);
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
        
        nanosleep(&(struct timespec){0, LOOPTIME}, NULL);
    }

    return 0;
}
