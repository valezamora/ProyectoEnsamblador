#include <linux/init.h>           // Macros used to mark up functions e.g. __init __exit
#include <linux/module.h>         // Core header for loading LKMs into the kernel
#include <linux/device.h>         // Header to support the kernel Driver Model
#include <linux/kernel.h>         // Contains types, macros, functions for the kernel
#include <linux/fs.h>             // Header for the Linux file system support
#include <linux/uaccess.h>          // Required for the copy to user function

#define  DEVICE_NAME "gMatrix"    ///< The device will appear at /dev/ebbchar using this value
#define  CLASS_NAME  "mat"        ///< The device class -- this is a character device driver
 
MODULE_LICENSE("GPL");            ///< The license type -- this affects available functionality
MODULE_VERSION("0.1");            

 
static struct class*  gMatrixClass  = NULL; ///< The device-driver class struct pointer
static struct device* gMatrixDevice = NULL; ///< The device-driver device struct pointer

static struct file_operations fops =
{
   .open = dev_open,
   .read = dev_read,
   .write = dev_write,
   .release = dev_release,
};

static int __init ebbchar_init(void){
   printk(KERN_INFO "EBBChar: Initializing the EBBChar LKM\n");
   return 0;
}
 
static void __exit ebbchar_exit(void){

   printk(KERN_INFO "EBBChar: Closing the gMatrixDriver\n");
}
module_init(ebbchar_init);
module_exit(ebbchar_exit);
void transform (int tranformsQuantity, char* transforms,int imageSize,char*image){
   extern transformarImagen;
   transformarImagen(tranformsQuantity,transforms,imageSize,image);
}
EXPORT_SYMBOL(transform);