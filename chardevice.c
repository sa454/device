

#include<linux/module.h>
#include<linux/init.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>


   
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Satyam");
 
int char_open(struct inode *, struct file *);
int char_close(struct inode *,struct file*);
ssize_t char_read(struct file *filp,char __user* ubuff,size_t count,loff_t *off);
ssize_t char_write(struct file *filp,const char __user* ubuff,size_t count,loff_t *off);
int ret; 
dev_t devno;                                  //declare the device number
unsigned char kbuff[10];

struct cdev _cdev;                            //declare the char device structure 
struct file_operations fops={
                                .open = char_open,
                                .release = char_close,  
                                .read = char_read,
                                .write = char_write                  
                              };
       

    


   int char_open(struct inode *inode_path, struct file *filp)
{ printk("cdev in inode of i_cdev %p\n",inode_path->i_cdev);
    printk("cdev address is in drive %p\n",&_cdev);
    
   printk("you are in open function\n");
    return 0;
}


   int char_close(struct inode *inode_path, struct file *filp)
{


   printk("you are in close function\n");
    return 0;
}

 unsigned char nbuff[6]= "BUDDY";	

   ssize_t char_read(struct file *filp,char __user* ubuff,size_t count,loff_t *off)
{  
   copy_to_user(ubuff,nbuff,6);
    printk("you are in read function\n");
    return 0;
}


   ssize_t char_write(struct file *filp,const char __user* ubuff,size_t count,loff_t *off)
{
   int i;
  printk("you are in write function\n");
  copy_from_user(kbuff,ubuff,10);
    
  for(i=0;i<count;i++)
{
   printk("Message from user :%c\n",kbuff[i]);
}
   return 0;
}


  static int __init char_init(void)
       {
       devno = MKDEV(42,0);                                    //static allocation of the device number or create device number
       ret = register_chrdev_region(devno,1,"test_first");       //registering the device with the kernel
       if(ret)
       {                                                       //error checking
	       printk("Error in register\n");
	       return ret;
       }
        
       cdev_init(&_cdev,&fops);         //attaching the file operations with the cdev structure

       cdev_add(&_cdev,devno,1);          //cdev structure associated with the device number in /dev file 


       printk("Inside the init function\n");
       return 0;
}





  static void __exit char_exit(void)
      {
       cdev_del(&_cdev);
       unregister_chrdev_region(devno,1);
       printk("inside the exit function\n");
      }
module_init(char_init);
module_exit(char_exit);




 	
