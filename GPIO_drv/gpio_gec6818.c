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
#include <asm/io.h>
#include "gpio_crl.h"

static volatile unsigned int *GPIOEOUT;
static volatile unsigned int *GPIOEOUTENB;
static volatile unsigned int *GPIOEALTFN0;
static volatile unsigned int *GPIOEALTFN1;


static int board_demo_gpio_init(int which)
{
    if(!GPIOEOUT)
    {
        GPIOEOUTENB = ioremap(0xC001E004,4);
        GPIOEOUT    = ioremap(0xC001E000,4);
    }
    
    *GPIOEOUTENB |= (1<<13);

    return 0;
}

static int board_demo_gpio_crl(int which,char status)
{
    if(status==1)
        *GPIOEOUT |= (1<<13);
    else
        *GPIOEOUT &= ~(1<<13);

    return 0;
}


static struct gpio_control gpio_crl={
    .num = 1,
    .init = board_demo_gpio_init,
    .crl = board_demo_gpio_crl,
};


struct gpio_control *get_gpio_control(void)
{
    return &gpio_crl;
}

