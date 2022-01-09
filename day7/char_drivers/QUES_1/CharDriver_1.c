// Initialization Functions
#include<linux/init.h>      // ?????????????????????????????????????
#include<linux/module.h>    // MODULE_LICENSE, MODULE_AUTHOR, MODULE_DESCRIPTION, Char_Driver_init, Char_Driver_exit, module_init(Char_Driver_init), module_exit(Char_Driver_exit)
#include<linux/kdev_t.h>    // device numbers : unknown declarations
#include<linux/types.h>     // For device numbers: unknown declarations for kdev_t.h to use, corrected in kdev_t.h file also.
#include<linux/fs.h>        // Registering and unregistering with device number, struct file_operations(.open, .release)
#include<linux/cdev.h>      // Allocating and deleting cdev structure, Registering cdev
#include<linux/kernel.h>

dev_t DevNo;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAIKUMAR");
MODULE_DESCRIPTION("CHAR DEVICE DRIVER");

// Function Prototypes
int CharDrivProg_open(struct inode *inode, struct file *filp);  // filp is the pointer to struct file
int CharDrivProg_release(struct inode *inode, struct file *filp);   //// filp is the pointer to struct file

// Structure that defines the operations that the driver provides.
struct file_operations fops =   // fops is a memory instance
{
    .open   = CharDrivProg_open,
    .release = CharDrivProg_release,
};

// Structure for the character driver
struct cdev *mychar_cdev;   // mychar_cdev is a pointer

// Struct that define the functionalities that driver provides
static int Char_Driver_init(void)
{
    // dev_t DevNo;
    int Major, Minor, Reg, RegDev;

    RegDev = alloc_chrdev_region(&DevNo, 0, 1, "CharDeviceDriver");
    Major = MAJOR(DevNo);
    Minor = MINOR(DevNo);
    printk(KERN_ALERT "\nWe are in init function\n");
    printk(KERN_ALERT "\nThe Major Number is %d...The Minor Number is %d\n",Major,Minor);

    if(RegDev < 0)
    {
        printk(KERN_ALERT "\nThe region requested for is not obtainable\n");
        return(-1);
    }
    mychar_cdev = cdev_alloc(); // allocate memory to Char Device structure
    mychar_cdev->ops = &fops;   // link our file operations to the char device

    Reg = cdev_add(mychar_cdev, DevNo, 1);   // Notify the kernel abt the new device
    if(Reg < 0)
    {
        printk(KERN_ALERT "\nDevice number and file _operations struct not linked\n");
        unregister_chrdev_region(DevNo, 1);
        return (-1);
    }
    return 0;
}

// Cleanup module
static void Char_Driver_exit(void)
{
    // dev_t DevNo;
    int Major, Minor;
    Major = MAJOR(DevNo);
    Minor = MINOR(DevNo);
    printk(KERN_ALERT "\nWe are exiting from the driver\n");
    printk(KERN_ALERT "\nThe Major Number is %d...The Minor Number is %d\n",Major,Minor);
    unregister_chrdev_region(DevNo, 1); // unregister the device number and the device created
    cdev_del(mychar_cdev);
    printk(KERN_ALERT "\nDeallocated Everything...bye bye...\n");
}

//Open System CAll
int CharDrivProg_open(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "\nThis is the Kernel Opennnnnnnnnnnnnn Callllllllllllll\n");
    return 0;
}

//Close System CAll
int CharDrivProg_release(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "\nThis is the kernel Closeeeeeeeeeeeee Callllllllllllll\n");
    return 0;
}

//Module over ride functions
module_init(Char_Driver_init);
module_exit(Char_Driver_exit);
