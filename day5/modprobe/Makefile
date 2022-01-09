	obj-m := mod1.o mod2.o

	KERNELDIR = /lib/modules/$(shell uname -r)/build

	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	depmod -a
	
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf /lib/modules/$(shell uname -r)/extra/*
	depmod -a
	