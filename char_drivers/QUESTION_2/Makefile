##ifneq($(KERNELRELEASE),)
obj-m := CharDriver_2.o

##else
KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o Application_2 Application_2.c
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm Application_2
install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
#endif
