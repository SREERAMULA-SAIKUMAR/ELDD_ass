#include<linux/init.h> // Required header for the initialization and cleanup functionalities
#include<linux/module.h> // This header contains the necessary stuff for the module
#include<linux/moduleparam.h> // This header allows the passing of parameter to the modules during insertion
#include<linux/kernel.h>

#include "Avg_of_Array.h"

MODULE_LICENSE("GPL"); // Macros that decide the license of the module
MODULE_AUTHOR("SAIKUMAR");
MODULE_DESCRIPTION("Avg of array numbers - module modprobe program");

int a[3]={1,2,3};

// Initialization function for the program
static int __init prog_init(void)
{
	printk(KERN_ALERT "We are going to do avg in module2\n");
	printk(KERN_ALERT "Avg of array is : %d\n", Avg_of_Array(a[3]));
	return 0;
}

// Cleanup function
static void __exit prog_exit(void)
{
        printk(KERN_ALERT "we are leaving in module2\n");
}

// Macros that allow the user to override the names of the mentioned functions with their own choice...
module_init(prog_init); // for initialization function
module_exit(prog_exit); // for cleanup function
