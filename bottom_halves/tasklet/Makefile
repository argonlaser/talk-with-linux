obj-m +=  tasklet_example.o

DIR := /lib/modules/$(shell uname -r)/build

all:
	make -C $(DIR) M=$(PWD) modules

clean:
	make -C $(DIR) M=$(PWD) clean
