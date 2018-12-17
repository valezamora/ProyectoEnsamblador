obj-m +=  mymodule1.o
obj-m +=  mymodule2.o
mymodule2-objs := transformaciones.o mymodule2-base.o

export KROOT=/lib/modules/$(shell uname -r)/build

allofit:  modules
	sudo insmod mymodule2.ko
	sudo insmod mymodule1.ko
modules: transformaciones.o
	@$(MAKE) -C $(KROOT) M=$(PWD) modules
modules_install:
	@$(MAKE) -C $(KROOT) M=$(PWD) modules_install
transformaciones.o: transformaciones.asm
	nasm -f elf64 transformaciones.asm
kernel_clean:
	@$(MAKE) -C $(KROOT) M=$(PWD) clean

clean: kernel_clean
	rm -rf   Module.symvers modules.order
