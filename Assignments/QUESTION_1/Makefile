##ifneq($(KERNELRELEASE),)
obj-m := CharDriver_1.o

##else
KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o Application_1 Application_1.c
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf Application_1
install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
#endif
