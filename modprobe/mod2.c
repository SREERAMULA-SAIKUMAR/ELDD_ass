#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

#include "add_sym.h"
#include "avg_sym.h"


MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAIKUMAR");
MODULE_DESCRIPTION("Add and Avg symbol modprobe programs");

static int prog_init(void)
{
	printk(KERN_ALERT "We are going to do add avg in module2\n");
	printk(KERN_ALERT "SUM : %d\n", add_sym(10,20));
	printk(KERN_ALERT "AVG : %d\n", avg_sym(10,20));

	return 0;
}

static void prog_cleanup(void)
{
        printk(KERN_ALERT "we are leaving in module2\n");
}

module_init(prog_init);
module_exit(prog_cleanup);
