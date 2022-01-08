// Initialization Functions.......
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/gpio.h>
#include<linux/uaccess.h>
#include<linux/interrupt.h>

#define NAME SSR    //Create a Device Number that can be used by the applications as well.....
#define SUCCESS 1
#define DEBOUNCE_TIME 200
static unsigned int gpioLED=49;
static unsigned int gpioSwitch=115;
static bool gpioVal=0;

unsigned long IRQflags=IRQF_TRIGGER_RISING;
static int irqNumber, numberPresses;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAIKUMAR");

//Function Prototypes
static irq_handler_t MyInterruptHandler(unsigned int irq, void *dev_id, struct pt_regs *regs);

//Init module
static int __init CharDevice_init(void)
{
    int result;

    if(!gpio_is_valid(gpioLED)){
        printk(KERN_INFO "GPIO_TEST: invalid LED GPIO\n");
        return -ENODEV;
    }
    gpio_request(gpioLED, "GPIO_49");   // gpioLED is hardcoded to 49, request it
    gpio_direction_output(gpioLED, 1);  // Set the gpio to be in output mode and on
    // gpio_set_value(gpioLED, ledon);  // Not required as set by line above (here for reference)
    gpio_export(gpioLED, false);

    if(!gpio_is_valid(gpioSwitch)){
        printk(KERN_INFO "GPIO_TEST: invalid Switch GPIO\n");
        return -ENODEV;
    }
    gpio_request(gpioSwitch, "GPIO_115");   // gpioSwitch is hardcoded to 115, request it
    gpio_direction_output(gpioSwitch, 1);  // Set the gpio switch to be in output mode and on
    // gpio_set_value(gpioSwitch, DEBOUNCE_TIME);  // Not required as set by line above (here for reference)
    gpio_export(gpioSwitch, false);

    irqNumber=gpio_to_irq(gpioSwitch);
    // printk(KERN_INFO "EBB Button: The button is mapped to IRQ: %d\n", irqNumber);

    // This next call requests an interrupt line
    result=request_irq(irqNumber,       // The interrupt number requested
                    (irq_handler_t)MyInterruptHandler,          // The pointer to handler function below
                    IRQflags,           // Use the custom kernel param to set interrupt type
                    "LED-SWITCH HANDLER",       // Used in /proc/interrupts to identify the owner
                    NULL);

    return 0;
}

//Cleanup module
void __exit CharDevice_exit(void)
{
    free_irq(irqNumber, NULL);
    gpio_unexport(gpioLED);
    gpio_unexport(gpioSwitch);

    printk(KERN_ALERT "\nI have unregistered the stuff that was allocated.....Goodbye for ever.....\n");
    return;
}

static irq_handler_t MyInterruptHandler(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
    gpioVal=!gpioVal;       // Invert the LED state on each button press
    gpio_set_value(gpioLED, gpioVal);       // Set the physical LED accordingly
    // getnstimeofday(&ts_current);         // Get the current time as ts_current
    // ts_diff=timespec_sub(ts_current, ts_last);       // Determine the time difference between last 2 presses
    // ts_last=ts_current;      // Store the current time as the last time ts_last 
    numberPresses++;        // Global counter, will be outputted when the module is unloaded
    printk(KERN_INFO "LED-SWITCH: Number of Interrups Generated: %d\n", numberPresses);
    return (irq_handler_t)IRQ_HANDLED;  //Announce that the IRQ has been handled correctly
}

//Module over ride functions
module_init(CharDevice_init);
module_exit(CharDevice_exit);
