#include<linux/init.h> // Required header for the initialization and cleanup functionalities
#include<linux/module.h> // This header contains the necessary stuff for the module
#include<linux/moduleparam.h>// This header allows the passing of parameter to the modules during insertion
#include<linux/kernel.h>

MODULE_LICENSE("GPL"); // Macros that decide the license of the module
MODULE_AUTHOR("SAIKUMAR");
MODULE_DESCRIPTION("Avg module modprobe program");

int my_avg(int a, int b)
{
	return ((a + b)/2);
}

/* Command to export symbol into kernel symbol table*/
EXPORT_SYMBOL_GPL(my_avg);

// Initialization function for the program
static int __init prog_init(void)
{
	printk(KERN_ALERT "Initialization of module1\n");

	return 0;
}

// Cleanup function
static void __exit prog_exit(void)
{       
        printk(KERN_ALERT "Exit of module1\n");
}

// Macros that allow the user to override the names  of the mentioned functions with their own choice...
module_init(prog_init); // for initialization function
module_exit(prog_exit); // for cleanup function
