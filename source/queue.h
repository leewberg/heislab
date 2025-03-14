/**
 * @file queue.h
 * @author Lee Wesenberg & Nicolay Pedersen Lindal
 * @brief Functions needed to do operations on the queue and the struct for the queue itself
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
#include "lights.h"
#define MAX_SIZE 2
#pragma once


/**
 * @struct Queue
 * @brief Struct containing all needed elements for a queue. The queue is structured so that it only has two elements at a time; one for up and one for down. Each of these elements contain two arrays themselves, each one with a length of the number of floors. The first of these elements tells us which direction the queue element is for, where a value of 0 means down and 1 means up. The second of these elements tell us which floors we're stopping. a -1 means that the spot is empty and that the elevator will skip that place in the order list
 * 
 */
typedef struct{
    int arr[MAX_SIZE][2][N_FLOORS];/**
    @brief  Array containing all queue elements. A 2x2x4 matrix*/
    int front;/**
    @brief Keeps track of our placement in the queue */
}Queue;

/**
 * @brief Initializes the queue
 * 
 * @param[out] q Queue
 */
void initQ (Queue* q);

/**
 * @brief Adds a floor to the queue based on the order's direction
 * 
 * @param[out] q Queue
 * @param[in] floor The floor getting added to the queue
 * @param[in] dir The direction of the order (either 0 (down) or 1 (up))
 */
void addFloorToQueue(Queue *q, int floor, int dir);


/**
 * @brief Removes everything from the queue.
 * 
 * @param[out] q Queue
 */
void wipeQueue(Queue* q);