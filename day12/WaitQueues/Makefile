obj-m:=waitqueue.o
KD=/lib/modules/$(shell uname -r)/build/
PWD:=$(shell pwd)

default:
	$(MAKE) -C $(KD) M=$(PWD) modules
	gcc -o write write.c
	gcc -o read read.c
	
clean:
	$(MAKE) -C $(KD) M=$(PWD) clean
	rm write read

install:
	$(MAKE) -C $(KD) M=$(PWD) modules_install
