/*
=====================================================================================================================
Driver Name : DEFERRED_KTIMERS
Author      : SAIKUMAR
Version     :
License     : GPL
Description : Sample driver code demonistrating the concept of kernel timers.
                        The driver code begins by initializing the timer variable , with init_timer().
                        Next the timer variable is filled with appropriate values and finally the
                        timer is registered with the kernel by add_timer().
                        Before the module is unloaded, the timer is deleted from the kernel by del_timer()
=====================================================================================================================
*/
#include "deferred_ktimers.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAIKUMAR");

unsigned int i=0;
/* Declare a timer variable */
struct timer_list ktimer;

/* Function executed once the timer is fired */
void sample_timer(struct timer_list *timer){
    PINFO("Inside the timer function with data = %d\n",i++);
    //reset the timer
    mod_timer(&ktimer, jiffies + msecs_to_jiffies(5000));
    /* To make the timer periodic, uncomment the folowing line */
    // add_timer(&ktimer);
}


//Initialization function
static int __init deferred_ktimers_init(void)
{
    PINFO("In init() function\n");

    /* Initialize the timer */
    // init_timer(&ktimer);
    timer_setup(&ktimer, &sample_timer, 0);
    /* Setup the timer parameters */
    // ktimer.data=100;                 /* Set a data(or address) to be accessed in the timer function */
    // ktimer.function=sample_timer;    /* Set the function to be called once the timer expires */
    // ktimer.expires=jiffies+100;      /* Set the delay value relative to jiffies */
    mod_timer(&ktimer, jiffies+msecs_to_jiffies(100));

    /* Register the timer with the kernel */
    // add_timer(&ktimer);

    PINFO("Timer added with an delay of 100ms\n");

    return 0;
}

//Cleanup module
void __exit deferred_ktimers_exit(void)
{
    PINFO("In init() function\n");

    /* Delete the timer entry from the kernel */
    del_timer(&ktimer);
}

//Module over ride functions
module_init(deferred_ktimers_init);
module_exit(deferred_ktimers_exit);
