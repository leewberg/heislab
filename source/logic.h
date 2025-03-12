/**
 * @file logic.h
 * @author Lee Wesenberg & Nicolay Pedersen Lindal
 * @brief Contains the function needed to sort the order for a floor once a button for that floor is pressed
 * @version 0.1
 * @date 2025-03-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once
#include "elevator.h"

/**
 * @brief Function that decides where a registered order for a floor is supposed to go based on the current direction and floor of the elevator and the order
 * 
 * @param[in, out] el Elevator
 * @param[out] q Queue
 * @param[in] f Floor we have recieved an order for
 * @param[in] b Button-type that was pressed
 */
void decideOrder(Elevator* el, Queue* q, int f, int b);