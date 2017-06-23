#Andrew Bossie
#Week 3

obj-m := procStats.o

#KDIR = /usr/src/linux-headers-4.10.0-14-generic

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules

clean:
	rm -rf *o *.ko *.mod.* *.symvers *.order