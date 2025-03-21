/**
 * @file elevator.h
 * @author Lee Wesenberg & Nicolay Pedersen Lindal
 * @brief h-file containing functions needed for the elevator and the elevator-struct itself
 * @version 0.1
 * @date 2025-03-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "queue.h"
#pragma once
#define LOOPTIME 1000*1000
#define RATIO 1000000000/(LOOPTIME)

/**
 * @struct Elevator
 * @brief Struct for the elements needed for an elevator
 */
typedef struct{
    int inFloor; /**
    @brief The floor the elevator is in */
    int orderList[N_FLOORS];/**
    @brief The elevator's currents list of orders*/
    int initialized;/**
    @brief Indicates if the elevator is initialized or not */
    int onOrderNum;/**
    @brief The element in its order list the elevator is on */
    int doorsOpen; /**
    @brief indicates if the doors are open */
    volatile int doorOpenCount; /**
    @brief Loop iterations the doors have been open for */
    int justStopped; /**
    @brief If the elevator just stopped or not */
    MotorDirection direction; /**
    @brief Direction of the current order the elevator is on */
    MotorDirection lastKnown; /**
    @brief Last known direction of the elevator. Used when returning to a floor after stop between floors */

} Elevator;

/**
 * @brief Moves the elevator to the next florr on its order list
 * 
 * @param[in, out] el Elevator
 * @param[in] floor Floor we're going to
 * @param[in] q Queue
 */
void goToFloor(Elevator* el, int floor, Queue* q);

/**
 * @brief Nullifies all orders on the elevators "personal" order list
 * 
 * @param[out] el Elevator
 */
void wipeOrders(Elevator* el);

/**
 * @brief Initializes the elevator
 * 
 * @param[in, out] el Elevator
 * @param[in] q Queue
 */
void initElevator(Elevator* el, Queue* q);


/**
 * @brief Returns the element at the start of the Queue. Also removes said element from the queue by moving the front up one value and nullifying the Queue element we're extracting from the queue.
 * 
 * @param[in, out] q Queue
 * @param[out] el Elevator
 */
void getnextElement(Queue *q, Elevator* el);

/**
 * @brief Function to deal with stop button being pressed. Stops elevator and wipes all orders + lights
 * 
 * @param[in, out] el Elevator
 * @param[out] q Queue
 */
void stopButton(Elevator* el, Queue* q);

/**
 * @brief Function to run when the elevator has just been stopped to return it to its previous state before it can continue as usual
 * 
 * @param[in, out] el Elevator
 * @param[out] q Queue
 */
void returnAfterStop(Elevator* el, Queue* q);

/**
 * @brief Prints all elements in the big and elevator queue. mainly used for debugging
 * 
 * @param[in] q Queue
 * @param[in] el Elevator
 */
void printQandE(Queue* q, Elevator* el);