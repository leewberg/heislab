# heislab
Code for project in TTK4235 Embedded Systems

## TODO:

### In lights.h: (N)
* make function that lights up every floor in correct direction based on the SuperQueue (defined in queue.h) and Elevator.OrderList (make sure to only light those from onOrderNum and onwards)

* make sure that elevator panel (the one on the outside) has correct logic, so that it continues to light up until the elevator arrives

* make function to extinguish all lights (used when queue is wiped)

### In queue.h (N)
* make sorting-function to sort order list in either direction

* extinguish all lights when wiping queue

* decide if we have to nullify queue.arr when wiping it


### In main.c (last thing to do, I think)
* add extra logic to add orders taken from the elevator panel to queue based on relative position

* get logic working (see spaghetti-code for refrence:P)

* an easy way of making sure we only add a floor to the list once and keep the queue in order is to init every value as -1, and add the floors. this way, we can just say that an order for floor 2 (1-indexed, direction up) will be added to the queue list for upwards direction on the element with index 1 (remember, queue is 0-indexed). this way, we can also make sure that we can skip orders, as any order that is for -1 will be read as invalid.
    * an example of an order list is then [-1, 1, 2, -1]. here, we go upwards and stop by floors 2 and 3, but don't stop in floors 1 and 4. 
    * also, lets say that we're going up, and someone in floor 1 already pressed the button for floor 4. if then someone else enters the elevator on floor 2 and also pressed the cab button for floor 4, we will only say that the current queue's 4th element (element on index 3 in array) is 3, and the elevator won't give a shit if we say this once or five times
        * if we're changing the queue to this, we need to make changes in elevator.c -> go to floor (and getNextElement?), queue.c -> initQ, and queue.c -> addToQueue

* once a button is pressed, we light it up at once. when the order is finished, we extinguish both the lights on the outside and inside of the cab. this makes the code more effective, as we don't need to check every single order to see if we need to light up the lamp or not.

### DONE:D
* light indicator for which floor we're on

* initialize elevator

* get doors working :3

* open doors for 3 seconds when we've reached a new floor (need to reset this if there's an obstruction)
    * can use a counter-variable in the elevator to keep track of how long the doors have been open. if an obstrucction is detected, we reset this variable. once the variable is the amount it should be (time used to run through the loop*amount of times it needs to run though the loop for it to be (about) 3s), it gets reset again and move on to the next order

* get the next queue-element in getNextOrder (can be combined with getNextElement?)

* get doors working :3

* expand on stop function to check if we stop inbetween floors or not. if we stop in a floor, the doors have to open.

* make just_stopped function

* start the entire while loop w/ checking if we're stopping or not

* extinguish light for order light when order is completed (as in, extinguish 2-UP when we've gone to the second floor)

* open doors if the elevator is stopped in a floor. keep the doors open for another three seconds once the stop button is released