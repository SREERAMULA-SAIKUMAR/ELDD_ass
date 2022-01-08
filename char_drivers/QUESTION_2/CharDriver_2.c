// Initialization Functions
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

#define NAME DESD_Device

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAIKUMAR");
MODULE_DESCRIPTION("A READ WRITE CHAR DEVICE DRIVER");

// Function Prototypes
int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);
ssize_t NAME_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);
ssize_t NAME_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp);

// Structure that defines the operations that the driver provides.
struct file_operations fops =
{
    .owner  = THIS_MODULE,
    .open   = NAME_open,
    .read   = NAME_read,
    .write  = NAME_write,
    .release= NAME_release,
};

// Structure for a character driver
struct cdev *my_cdev;

// Init module
static int __init CharDevice_init(void)
{
    int result;
    int MAJOR, MINOR;
    dev_t Mydev;
    Mydev = MKDEV(100,0);   // Create a device number
    MAJOR = MAJOR(Mydev);
    MINOR = MINOR(Mydev);
    printk(KERN_ALERT "\nWe are in init function\n");
    printk(KERN_ALERT "\nThe Major Number is %d...The Minor Number is %d\n",MAJOR,MINOR);
    result = register_chrdev_region(Mydev,1,"DESD_Device"); // register device region...
    if(result<0)
    {
        printk(KERN_ALERT "\nThe region requested for is not obtainable\n");
        return(-1);
    }
    my_cdev = cdev_alloc(); // allocate memory to Char Device structure
    my_cdev->ops = &fops;   // link our file operations to the char device

    result = cdev_add(my_cdev,Mydev,1);   // Notify the kernel abt the new device
    if(result<0)
    {
        printk(KERN_ALERT "\nThe Char Device has not been created\n");
        unregister_chrdev_region(Mydev, 1);
        return (-1);
    }
    return 0;
}

// Cleanup module
void __exit CharDevice_exit(void)
{
    dev_t Mydev;
    int MAJOR, MINOR;
    Mydev = MKDEV(100,0);
    MAJOR = MAJOR(Mydev);
    MINOR = MINOR(Mydev);
    printk(KERN_ALERT "\nWe are exiting from the driver\n");
    printk(KERN_ALERT "\nThe Major Number is %d...The Minor Number is %d\n",MAJOR,MINOR);
    unregister_chrdev_region(Mydev, 1); // unregister the device number and the device created
    cdev_del(my_cdev);
    printk(KERN_ALERT "\nI have unregistered the stuff that was allocated...bye bye...\n");
//  return;
}

//Open System CAll
int NAME_open(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "\nThis is the Kernel Open Call\n");
    return 0;
}

//Close System CAll
int NAME_release(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "\nThis is the kernel release system call\n");
    return 0;
}

//Write Functionality
ssize_t NAME_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp)
{
    char Kbuff[100];
    unsigned long result;
    ssize_t retval;
    //strcpy(Kbuff,Ubuff);
    result=copy_from_user((char *)Kbuff,(char *)Ubuff,count);   // get user data

    if(result == 0)
    {
        printk(KERN_ALERT "\nMessage from the user ==> %s\n", Kbuff);   // received data from the user application
        printk(KERN_ALERT "\nData successfully written\n");
        retval = count;
        printk(KERN_ALERT "\nNo. of bytes received fron user application to kernel\n");
        return retval;
    }
    else if (result>0)
    {
        printk(KERN_ALERT "\nMessage from the user ==> %s\n", Kbuff);
        printk(KERN_ALERT "\nPart Data Copied from user application to kernel\n");
        retval = (count-result);
        printk(KERN_ALERT "\nData bytes: %ld\n", retval);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "\nError Writing Data\n");
        retval = -EFAULT;
        return retval;
    }
}

//Read Functionality
ssize_t NAME_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp)
{
    char Kbuff[] = "This is some data from the kernel to the user.\n";
    unsigned long result;
    ssize_t retval;
    printk(KERN_ALERT "The value of count: %ld\n", count);
    result = copy_to_user((char *)Ubuff,(char *)Kbuff,count);//copy to user
    if(result == 0)
    {
        //printk(KERN_ALERT "\nMessage from the user ==> %s\n", Kbuff);
        printk(KERN_ALERT "\nData successfully read\n");
        retval=count;
        return retval;
    }
    else if (result>0)
    {
        printk(KERN_ALERT "\nPart Data available\n");
        retval = (count - result);
        printk(KERN_ALERT "\nNo. of bytes received from kernel: %ld\n", retval);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "\nError Writing Data to User\n");
        retval = -EFAULT;
        return retval;
    }
}

//Module over ride functions
module_init(CharDevice_init);
module_exit(CharDevice_exit);
