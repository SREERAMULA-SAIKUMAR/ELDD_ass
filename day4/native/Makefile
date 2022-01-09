obj-m := hello.o

KDIR=/lib/modules/$(shell uname -r)/build/

PWD=$(shell pwd)


all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -c $(KDIR) M=$(PWD) clean
