obj-m := modulo.o
KDIR ?= /lib/modules/`uname -r`/build
PWD := `pwd`
default:
	make -C $(KDIR) M=$(PWD) modules