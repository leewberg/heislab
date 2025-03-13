/**
 * @file lights.h
 * @author Lee Wesenberg & Nicolay Pedersen Lindal
 * @brief Contains function to extinguish all light-indicators
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
#pragma once

/**
 * @brief Extinguishes all light-indicators. Takes no parametres
 * 
 */
void extLightIndicators();