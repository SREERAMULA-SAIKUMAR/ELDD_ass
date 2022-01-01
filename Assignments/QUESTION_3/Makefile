##ifneq($(KERNELRELEASE),)
obj-m := CharDriver_3.o

##else
KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o Application_3 Application_3.c
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf Application_3
install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
#endif
