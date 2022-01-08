//Initialization Functions
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/slab.h> 
#include<linux/uaccess.h>
#include<linux/ioctl.h>

#define NAME MyCharDevice

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAIKUMAR");

//Function Prototypes
int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);
ssize_t NAME_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);
ssize_t NAME_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp);
long NAME_ioctl(struct file * filp, unsigned int cmd, unsigned long arg);

//Structure that defines the operations that the driver provides
struct file_operations fops =
{
    .owner  = THIS_MODULE,
    .open   = NAME_open,
    .read   = NAME_read,
    .write  = NAME_write,
    .release= NAME_release,
    .unlocked_ioctl  = NAME_ioctl,
};

struct DefaultData{
    int Baudrate;
    int StopBits;
    int Parity;
};

dev_t Mydev;

//Structure for a character driver
struct cdev *my_cdev;

//Init module
static int __init CharDevice_init(void)
{
    int result;
    int MAJOR,MINOR;
    // dev_t Mydev;
    // Mydev = MKDEV(255,0);// Create a device number
    MAJOR=MAJOR(Mydev);
    MINOR=MINOR(Mydev);
    result=alloc_chrdev_region(&Mydev,0,1,"MyCharDevice");// register device region.........
    // result=register_chrdev_region(Mydev,1,"MyCharDevice");//register device region...
    if(result<0)
    {
        printk(KERN_ALERT "\nThe region requested for is not obtainable\n");
        return(-1);
    }
    MAJOR=MAJOR(Mydev);
    MINOR=MINOR(Mydev);
    printk("\nThe Major Number is %d...The Minor Number is %d\n",MAJOR,MINOR);
    my_cdev = cdev_alloc();//allocate memory to Char Device structure
    my_cdev->ops = &fops;//link our file operations to the char device

    result=cdev_add(my_cdev,Mydev,1);//Notify the kernel abt the new device
    if(result<0)
    {
        printk(KERN_ALERT "\nThe Char Device has not been created.....\n");
        // unregister_chrdev_region(Mydev, 1);
        return (-1);
    }
    return 0;
}

//Cleanup module
void __exit CharDevice_exit(void)
{
    // dev_t Mydev;
    int MAJOR,MINOR;
    // Mydev=MKDEV(255,0);
    MAJOR=MAJOR(Mydev);
    MINOR=MINOR(Mydev);
    printk("\nThe Major Number is %d...The Minor Number is %d\n",MAJOR,MINOR);
    unregister_chrdev_region(Mydev, 1);//unregister the device numbers and the device created
    cdev_del(my_cdev);
    printk(KERN_ALERT "\nIhave unregistered the stuff that was allocated.....Goodbye for ever.....\n");
    return;
}

//Open System CAll
int NAME_open(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "\nThis is the Kernel....Open System Call....\n");
    return 0;
}

//Close System CAll
int NAME_release(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "This is the release method of my Character Driver......Bye Dudes.....\n");
    return 0;
}

//Write Functionality
ssize_t NAME_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp)
{
    char Kbuff[80];
    unsigned long result;
    ssize_t retval;
    //strcpy(Kbuff,Ubuff);
    result=copy_from_user((char *)Kbuff,(char *)Ubuff,count);
    if(result==0)
    {
        printk(KERN_ALERT "\nMessage from the user.....\n>>>>> %s <<<<<\n",Kbuff);
        printk(KERN_ALERT "\nData successfully written.....\n");
        retval=count;
        return retval;
    }
    /*else if (result>0)
    {
        printk(KERN_ALERT "\nMessage from the user.....\n>>>> %s <<<<<\n",Kbuff);
        printk(KERN_ALERT "\nPart Data Copied.....\n");
        retval=(count-result);
        return retval;
    }*/
    else
    {
        printk(KERN_ALERT "\nError Writing Data\n");
        retval=-EFAULT;
        return retval;
    }
}

//Read Functionality
ssize_t NAME_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp)
{
    char Kbuff[]="This is some data from the kernel to the user....User, ENJOY.....";
    unsigned long result;
    ssize_t retval;
    //strcpy(Kbuff,Ubuff);
    result=copy_to_user((char *)Ubuff,(char *)Kbuff,count);//copy to user
    if(result==0)
    {
        //printk(KERN_ALERT "\nMessage from the user.....\n>>>>> %s <<<<<\n",Kbuff);
        printk(KERN_ALERT "\nData successfully read.....\n");
        retval=count;
        return retval;
    }
    /*else if (result>0)
    {
        //printk(KERN_ALERT "\nMessage from the user.....\n>>>> %s <<<<<\n",Kbuff);
        printk(KERN_ALERT "\nPart Data available.....\n");
        retval=(count-result);
        return retval;
    }*/
    else
    {
        printk(KERN_ALERT "\nError Writing Data to User\n");
        retval=-EFAULT;
        return retval;
    }
}

long NAME_ioctl(struct file * filp, unsigned int cmd, unsigned long arg)
{
    unsigned int temp, STOP_BITS;
    ssize_t retval=SUCCESS;
    char Ubuff[20];
    struct DefaultData *ToSend;
    printk("\nIOCTL function");
    switch(cmd){
        case SET_BAUD_RATE:
            get_user(temp,(int __user *)arg);
            printk("\nSetting the Baud Rate to %ld",temp);
            temp=10;
            put_user(temp,(int __user *)arg);
            break;
        case SET_DIRECTION_WRITE:
            printk("\nThe Direction is set to write");
            break;
        case SET_NO_STOP_BITS:
            get_user(STOP_BITS,(int __user *)arg);
            printk("\nSetting the Num of Stop bits to %d", STOP_BITS);
            break;
        case DEFAULT_DATA:
            ToSend=(struct DefaultData *)Ubuff;
            copy_from_user(Ubuff, (struct  DefaultData *)arg, sizeof(struct DefaultData));
            printk("Default Data is %d, %d, %d", ToSend->Baudrate);
            break;
        default:
            printk("\nCommand Not Found");
            return (-EINVAL);
    }
    return (retval);
}

//Module over ride functions
module_init(CharDevice_init);
module_exit(CharDevice_exit);
