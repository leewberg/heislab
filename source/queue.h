#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

struct queue
{
    int inQueue;
};

void addToQueue();
void wipeQueue();
void lightOrderButton();
void extOrderButton();
