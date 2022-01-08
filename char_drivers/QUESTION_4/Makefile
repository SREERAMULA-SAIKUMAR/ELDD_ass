obj-m := CharDriver_4.o

KERNELDIR = /lib/modules/$(shell uname -r)/build/
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o Application_4 Application_4.c
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf Application_4
install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
