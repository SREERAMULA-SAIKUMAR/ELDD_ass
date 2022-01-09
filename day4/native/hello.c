#include<linux/module.h>
#include<linux/init.h>

int  hello_init(void)
{
	printk(KERN_ALERT "HELLO TO ALL\n");
	return 0;
}

void hello_exit(void)
{
	printk(KERN_ALERT "BYE TO ALL\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
