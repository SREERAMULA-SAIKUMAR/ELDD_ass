##ifneq($(KERNELRELEASE),)
obj-m := ioctl_driver.o

##else
KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o ioctl_application ioctl_application.c
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm ioctl_application
install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
#endif
