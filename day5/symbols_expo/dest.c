#include<linux/init.h> // Required header for the initialization and cleanup functionalities
#include<linux/module.h> // This header contains the necessary stuff for the module
#include<linux/moduleparam.h> // This header allows the passing of parameter to the modules during insertion
#include<linux/kernel.h>
#include"my_add.h"

MODULE_LICENSE("GPL"); // Macros that decide the license of the module
MODULE_AUTHOR("SAIKUMAR");

static int one = 1;
static int two = 2;

// Initialization function for the program
static int __init add_init(void)
{
	printk(KERN_ALERT "We are going to add\n");
	printk(KERN_ALERT "ADD Result is : %d\n", my_add(one,two));
	return 0;
}

// Cleanup function
static void __exit add_exit(void)
{
        printk(KERN_ALERT "we are leaving\n");
}

// Macros that allow the user to override the names of the mentioned functions with their own choice...
module_init(add_init); // for initialization function
module_exit(add_exit); // for cleanup function
