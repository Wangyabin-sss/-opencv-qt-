#ifndef _GPIO_CRL_H
#define _GPIO_CRL_H

struct gpio_control
{
    int num;
	int (*init) (int which); /* 初始化LED, which-哪个LED */       
	int (*crl) (int which, char status); /* 控制LED, which-哪个LED, status:1-亮,0-灭 */
};

struct gpio_control *get_gpio_control(void);

#endif

