# heislab
Code for project in TTK4235 Embedded Systems

## TODO:
### In lights.h: (N)
* make function that lights up every floor in correct direction based on the SuperQueue (defined in queue.h) and Elevator.OrderList (make sure to only light those from onOrderNum and onwards)

* make sure that elevator panel (the one on the outside) has correct logic, so that it continues to light up until the elevator arrives

* make function to extinguish all lights (used when queue is wiped)


### In elevator.h (L)

* extinguish light for order light when order is completed (as in, extinguish 2-UP when we've gone to the second floor)

* expand on stop function to check if we stop inbetween floors or not. if we stop in a floor, the doors have to open.
    * can do this by checking elevio_floors and if it's -1 or not. if not, we open the doors. also close doors once we haven't stopped yet.
* make just_stopped function
    * go-to-floor for last recorded floor in elevator history, close doors, and don't take orders. yippeeee


### In queue.h (N)
* make sorting-function to sort order list in either direction

* extinguish all lights when wiping queue

* decide if we have to nullify queue.arr when wiping it


### In main.c (last thing to do, I think)
* add extra logic to add orders taken from the elevator panel to queue based on relative position

* get logic working (see spaghetti-code for refrence:P)

* start the entire while loop w/ checking if we're stopping or not


### DONE:D
* light indicator for which floor we're on

* initialize elevator

* get doors working :3

* open doors for 3 seconds when we've reached a new floor (need to reset this if there's an obstruction)
    * can use a counter-variable in the elevator to keep track of how long the doors have been open. if an obstrucction is detected, we reset this variable. once the variable is the amount it should be (time used to run through the loop*amount of times it needs to run though the loop for it to be (about) 3s), it gets reset again and move on to the next order

* get the next queue-element in getNextOrder (can be combined with getNextElement?)

* get doors working :3