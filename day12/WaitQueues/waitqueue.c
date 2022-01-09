#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/wait.h>
#include<linux/kthread.h>

//struct class *dev_class;
struct cdev my_cdev;
dev_t dev;
wait_queue_head_t wq;

//declaration:
int WQQ_open(struct inode *inode,struct file *filp);
ssize_t WQQ_read(struct file *filp,char __user *ubuff,size_t count,loff_t *offp);
ssize_t WQQ_write(struct file *filp, const char __user *ubuff,size_t count,loff_t *offp);
int WQQ_release(struct inode *inode,struct file *filp);

struct file_operations fops=
{
    .owner  =   THIS_MODULE,
    .open   =   WQQ_open,
    .read   =   WQQ_read,
    .write  =   WQQ_write,
    .release=   WQQ_release,
};

static int __init WQQ_init(void)
{
    
    if((alloc_chrdev_region(&dev,25,1,"WQQ"))<0)
    {
        printk("\n cannot create major number..");
        return -1;
    }
    printk(KERN_ALERT "\n major number =%d,minor number =%d",MAJOR(dev),MINOR(dev));

    // creating cdev structure
    cdev_init(&my_cdev,&fops);

    // adding major number with cdev

    if((cdev_add(&my_cdev,dev,1))<0)
    {
        printk("\n cannot add major number and cdev.\n");
        unregister_chrdev_region(dev,1);
        return -1;
    }
    
    // initialize wait queue
    init_waitqueue_head(&wq);
    
    printk("\n device driver loaded..\n");
    return 0;  
    
}

static void __exit WQQ_exit(void)
{
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev,1);
    printk("device driver unloaded..\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAIKUMAR");

module_init(WQQ_init);
module_exit(WQQ_exit);

char kbuff[60];
int size_kbuff=0;
int WQQ_open(struct inode *inode,struct file *filp)
{
    printk("\n device file opened..\n");
    return 0;
}

ssize_t WQQ_read(struct file *filp,char __user *ubuff,size_t count,loff_t *offp)
{
    unsigned long result;
    ssize_t retval;
    if(size_kbuff==0)
    {
        wait_event(wq,size_kbuff>0);
    }
    result=copy_to_user((char*)ubuff,(char*)kbuff,count);
    if(result==0)
    {
        printk(KERN_ALERT "\n MESSAGE TO USER..\n...%s....\n",kbuff);
        printk(KERN_INFO  "\n DATA SEND COMPLETED..\n");
        retval=count;
        return retval;
    }
    else if(result>0)
    {  
        printk(KERN_ALERT "\n MESSAGE TO USER..\n...%s....\n",kbuff);
        printk(KERN_ALERT "\n THE PART OF DATA IS SENDED..\n ");
        retval=(count-result);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "\n ERROR IN READING");
        retval=-EFAULT;
        return retval;
    }
}

ssize_t WQQ_write(struct file *filp, const char __user *ubuff,size_t count,loff_t *offp)
{
    unsigned long result;
    ssize_t retval;
    result=copy_from_user((char*)kbuff,(char*)ubuff,count);
    size_kbuff=(count-result);
    wake_up(&wq);
    if(result==0)
    {
        printk(KERN_ALERT "\n MESSAGE FROM USER..\n...%s....\n",ubuff);
        printk(KERN_INFO  "\n DATA RECEIVED COMPLETED..\n");
        retval=count;
        return retval;
    }
    else if(result>0)
    {  
        printk(KERN_ALERT "\n MESSAGE FROM USER..\n...%s....\n",ubuff);
        printk(KERN_ALERT "\n THE PART OF DATA IS RECEIVED..\n ");
        retval=(count-result);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "\n ERROR IN WRITING");
        retval=-EFAULT;
        return retval;
    }
}
int WQQ_release(struct inode *inode,struct file *filp)
{
    printk("\n device file opened..\n");
    return 0;
}
