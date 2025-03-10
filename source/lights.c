#include "lights.h"

void extLightIndicators() {//extinguish all cab and order lights (for example when stop button is pressed or we wipe the q)
    for(int f = 0; f < N_FLOORS; f++){ 
        for(int b = 0; b < N_BUTTONS; b++){
            elevio_buttonLamp(f, b, 0); //go through each button and turn off the corresponding light
            }
        }
}