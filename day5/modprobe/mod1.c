#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAIKUMAR");
MODULE_DESCRIPTION("Add and Avg symbol modprobe programs");

int add_sym(int a, int b)
{
	return (a + b);
}

int avg_sym(int c, int d)
{
	return ((c + d)/2);
}

EXPORT_SYMBOL_GPL(add_sym);
EXPORT_SYMBOL_GPL(avg_sym);


static int prog_init(void)
{
	printk(KERN_ALERT "Initialization of module1\n");

	return 0;
}

static void prog_cleanup(void)
{       
        printk(KERN_ALERT "Exit of module2\n");
}

module_init(prog_init);
module_exit(prog_cleanup);
