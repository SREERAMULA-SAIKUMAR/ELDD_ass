//Initialization Functions
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

#define ADD MyAddDevice

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAIKUMAR");
MODULE_DESCRIPTION("ADDITION CHAR DRIVER");

//Structure for a character driver
struct cdev *my_cdev;

//Function Prototypes
int ADD_open(struct inode *inode, struct file *filp);
int ADD_release(struct inode *inode, struct file *filp);
ssize_t ADD_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);
ssize_t ADD_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp);

//Structure that defines the operations that the driver provides
struct file_operations fops =
{
    .owner  = THIS_MODULE,
    .open   = ADD_open,
    .read   = ADD_read,
    .write  = ADD_write,
    .release= ADD_release,
};

int MAJOR,MINOR;
dev_t Mydev;

//Init module
static int __init CharDevice_init(void)
{
    int result;
    Mydev = MKDEV(15,0);// Create a device number
    MAJOR=MAJOR(Mydev);
    MINOR=MINOR(Mydev);
    printk(KERN_INFO "\nThe Major Number is %d...The Minor Number is %d\n",MAJOR,MINOR);
    result=register_chrdev_region(Mydev,1,"MyAddDevice");//register device region...
    if(result<0)
    {
        printk(KERN_ALERT "\nThe region requested for is not obtainable\n");
        return(-1);
    }
    my_cdev = cdev_alloc();//allocate memory to Char Device structure
    my_cdev->ops = &fops;//link our file operations to the char device

    result=cdev_add(my_cdev,Mydev,1);//Notify the kernel abt the new device
    if(result<0)
    {
        printk(KERN_ALERT "\nThe Char Device has not been created.....\n");
        unregister_chrdev_region(Mydev, 1);
        return (-1);
    }
    return 0;
}

//Cleanup module
void __exit CharDevice_exit(void)
{
    // Mydev=MKDEV(255,0);
    // MAJOR=MAJOR(Mydev);
    // MINOR=MINOR(Mydev);
    printk("\nThe Major Number is %d...The Minor Number is %d\n",MAJOR,MINOR);
    unregister_chrdev_region(Mydev, 1);//unregister the device numbers and the device created
    cdev_del(my_cdev);
    printk(KERN_ALERT "\nAll Things Removed.....\n");
    return;
}
//Module over ride functions
module_init(CharDevice_init);
module_exit(CharDevice_exit);

//Open System CAll
int ADD_open(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "\nThis is the Kernel....Open Call....\n");
    return 0;
}

//Close System CAll
int ADD_release(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "This is the release method of my Character Driver......\n");
    return 0;
}
int sum;
//Write Functionality
ssize_t ADD_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp)
{
    char Kbuff[100];
    unsigned long result;
    ssize_t retval;

    result=copy_from_user((char *)Kbuff,Ubuff,count);
    if(result==0)
    {
        printk(KERN_ALERT "\nMessage from the user ..\n >> %d %d <<\n",(int)Kbuff[0],(int)Kbuff[1]);
        printk(KERN_ALERT "\nData Received Successfully.....\n");
        sum=(int)Kbuff[0]+(int)Kbuff[1];
        printk(KERN_ALERT "\n Kbuff %d..\n",sum);
        retval=count;
        return retval;
    }
    else if (result>0)
    {
        printk(KERN_ALERT "\nMessage from the user.....\n>>>> %s <<<<<\n",Kbuff);
        printk(KERN_ALERT "\nPart Data Copied.....\n");
        retval=(count-result);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "\nError Writing Data\n");
        retval=-EFAULT;
        return retval;
    }
}

//Read Functionality
ssize_t ADD_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp)
{
    char Kbuff[100];
    unsigned long result;
    ssize_t retval;
    sprintf(Kbuff,"%d",sum);
    result=copy_to_user((char *)Ubuff,(char *)Kbuff,sizeof(Kbuff));//copy to user
    if(result==0)
    {
        //printk(KERN_ALERT "\nMessage from the user.....\n>>>>> %s <<<<<\n",Kbuff);
        printk(KERN_ALERT "\nData successfully read.....\n");
        retval=count;
        return retval;
    }
    else if (result>0)
    {
        //printk(KERN_ALERT "\nMessage from the user.....\n>>>> %s <<<<<\n",Kbuff);
        printk(KERN_ALERT "\nPart Data available.....\n");
        retval=(count-result);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "\nError Writing Data to User\n");
        retval=-EFAULT;
        return retval;
    }
}

