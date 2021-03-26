obj-m +=gpio_led.o
gpio_led-y :=gpio_gec6818.o gpio.o
KERNEL_DIR :=/home/ubuntu/6818GEC/kernel
CROSS_COMPILE :=/home/ubuntu/6818GEC/prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi-

PWD:=$(shell pwd)

default:
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	rm  *.o *.order .*.cmd  *.mod.c *.symvers .tmp_versions -rf



