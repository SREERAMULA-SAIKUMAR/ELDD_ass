##ifneq($(KERNELRELEASE),)
obj-m := CharDriver_4.o

##else
KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o Application_4 Application_4.c
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm Application_4
install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
#endif
