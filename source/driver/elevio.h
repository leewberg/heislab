#pragma once


#define N_FLOORS 4

typedef enum { 
    DIRN_DOWN   = -1,
    DIRN_STOP   = 0,
    DIRN_UP     = 1
} MotorDirection;


#define N_BUTTONS 3

typedef enum { //int vals of buttons for each floor
    BUTTON_HALL_UP      = 0,
    BUTTON_HALL_DOWN    = 1,
    BUTTON_CAB          = 2
} ButtonType;


void elevio_init(void);

void elevio_motorDirection(MotorDirection dirn); //direction of elevator
void elevio_buttonLamp(int floor, ButtonType button, int value); //lights of or extinguishes lamp for button
void elevio_floorIndicator(int floor); //lights up or extinguished floor lamp
void elevio_doorOpenLamp(int value); //lights up or extinguishes the door open lamp
void elevio_stopLamp(int value); //lights up or extinguishes the stop lamp

int elevio_callButton(int floor, ButtonType button); 
int elevio_floorSensor(void); //tells us which floor we're on
int elevio_stopButton(void);
int elevio_obstruction(void);

