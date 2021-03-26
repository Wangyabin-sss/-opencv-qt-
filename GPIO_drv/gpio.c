#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/major.h>
#include <linux/io.h>
#include <linux/ioctl.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/device.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/tty.h>
#include <linux/uaccess.h>
#include <linux/kmod.h>
#include <asm/io.h>
#include <linux/gfp.h>
#include "gpio_crl.h"


/* 1. 确定主设备号   */
static int major = 0;
static struct class *gpio_class;
static struct gpio_control *gpio_crl;


static ssize_t gpio_drv_read (struct file *file, char __user *buf, size_t size, loff_t *offset)
{
    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	return 0;
}
/* write(fd,&val,1); */
static ssize_t gpio_drv_write (struct file *file, const char __user *buf, size_t size, loff_t *offset)
{
    int err;
	char status;
	//struct inode *inode = file_inode(file);
	int minor ;//= iminor(inode);
	
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	err = copy_from_user(&status, buf, 1);
    printk("gpio_drv_write %d\n",err);
	/* 根据次设备号和status控制LED */
	gpio_crl->crl(minor, status);
	
	return 1;
}
static long gpio_drv_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}
static int gpio_drv_open (struct inode *node, struct file *file){
    int minor;
    //int minor = iminor(node);
	
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	/* 根据次设备号初始化LED */
    gpio_crl->init(minor);
	
	return 0;
}
static int gpio_drv_close (struct inode *node, struct file *file){

    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	return 0;
}

static struct file_operations gpio_drv = {
	.owner	        = THIS_MODULE,
	.open           = gpio_drv_open,
	.read           = gpio_drv_read,
	.write          = gpio_drv_write,
    .unlocked_ioctl = gpio_drv_ioctl,
	.release        = gpio_drv_close,
};

static int __init gpio_init(void)
{
    int err,i;
    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	major = register_chrdev(0, "gpio_led", &gpio_drv);  

	gpio_class = class_create(THIS_MODULE, "gpio_led_class");
	err = PTR_ERR(gpio_class);

	if (IS_ERR(gpio_class)) {
		printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
		unregister_chrdev(major, "gpio_led");
		return -1;
	}

	gpio_crl = get_gpio_control();

	for (i = 0; i < gpio_crl->num; i++)
		device_create(gpio_class, NULL, MKDEV(major, i), NULL, "gpio_led%d", i); /* /dev/100ask_led0,1,... */

	return 0;
}

static int __exit gpio_exit(void)
{
    int i;
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);

	for (i = 0; i < gpio_crl->num; i++)
		device_destroy(gpio_class, MKDEV(major, i));

	device_destroy(gpio_class, MKDEV(major, 0));
	class_destroy(gpio_class);
	unregister_chrdev(major, "gpio_led");
}

module_init(gpio_init);
module_exit(gpio_exit);

MODULE_LICENSE("GPL");


