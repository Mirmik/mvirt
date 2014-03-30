
CCFLAGS= -I$(TOPDIR)/include  -I$(TOPDIR)/libc -I$(TOPDIR)/arch/include -I$(TOPDIR)/base/include -I$(TOPDIR)/board/include  -mcpu=arm926ej-s -O2 -Wall 
CPPFLAGS= $(CCFLAGS)  -I$(TOPDIR)/mvirt/include 
LDFLAGS = -TuImage2.lds  




USROBJ=$(TOPDIR)/usr/sketch.o





DEVDIR=${shell pwd}/..

CROSS_COMPILE=$(TOPDIR)/../g++_arm_none_eabi/bin/arm-none-eabi-
CPP = $(CROSS_COMPILE)g++
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump
TOPDIR=${shell pwd}

PRGARCH = boot regsight int_table
PRGBOARD =
PRGBASE = int_table   debug_serial debug_serial_c base_func
PRGMVIRT = hmain irq csh Debug command_list init _console ringbuffer boot2
PRGMVIRTU =  delay time Stream Print simple Serial


OBJARCH = $(addprefix arch/src/,$(PRGARCH))
OBJARCH := $(addsuffix .o,$(OBJARCH))
OBJBOARD = $(addprefix board/src/,$(PRGBOARD))
OBJBOARD := $(addsuffix .o,$(OBJBOARD))
OBJBASE = $(addprefix base/src/,$(PRGBASE))
OBJBASE := $(addsuffix .o,$(OBJBASE))
OBJMVIRT=$(addprefix mvirt/src/,$(PRGMVIRT))
OBJMVIRT:=$(addsuffix .o,$(OBJMVIRT))
OBJMVIRTU=$(addprefix mvirt/src/utility/,$(PRGMVIRTU))
OBJMVIRTU:=$(addsuffix .o,$(OBJMVIRTU))


OBJ = $(OBJARCH) $(OBJBOARD) $(OBJBASE) $(OBJMVIRT) $(OBJMVIRTU) $(USROBJ)



all: all2

all2: $(OBJ) $(OBJLIB) LINK DISASM OCPY 



LINK: 
	$(CPP) $(CPPFLAGS) $(LDFLAGS) $(OBJ) $(OBJLIB) -o uImage



DISASM:
	$(OBJDUMP) -d uImage > disasm

DISASMCPY:
	$(OBJDUMP) -D -marm --target binary ubl.bin > disasmcpy

OCPY:
	$(OBJCOPY) -O binary uImage uImage.bin
 

%.o:%.S
	$(CPP) $(CCFLAGS) -c $< -o $@


%.o:%.c
	$(CC) $(CCFLAGS) -c $< -o $@

%.o:%.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@





clean:
	rm -f $(TOPDIR)/base/src/*.o
	rm -f $(TOPDIR)/arch/src/*.o
	rm -f $(TOPDIR)/mvirt/src/*.o
	rm -f $(TOPDIR)/mvirt/src/utility/*.o


