
ECHO=$(V)echo -e
M_ECHO=echo -e
OUTPUT=> /dev/null


ifndef VERBOSE
    V=@
else
    V := $(shell if [ $(VERBOSE) = 1 ] ; then  echo "" ; fi )
endif

#SD card default name, DONT CHANGE THIS!!!
SDDEFNAME=/dev/sdX

#SD card device name, CHANGE THIS!!!
#for example, SDNAME=/dev/sdc
SDNAME=/dev/sdb



all: build install

build: tools ublbuild kernelbuild 

rebuild: clean build

kernelbuild:
	make --directory=kernel

dumount:
	sudo umount -f $(SDNAME)1 | echo 
	sudo umount -f $(SDNAME)2 | echo

tools:
	make --directory=uflash

ublbuild:
	make --directory=ubl


install: install_intro install_dd dumount prepare_partitions_without_format install_bootloader2

install_dd:
	sudo dd if=/dev/zero of=$(SDNAME) count=1 bs=512

install_intro:
	$(ECHO) ""

	$(V)if [ ! $(SDNAME) ] ; then $(M_ECHO) "\033[31mEmpty SD card name, please set SDNAME variable\033[0m" ; $(M_ECHO) ""; exit 1; fi
	$(V)if [ "$(SDNAME)" == "$(SDDEFNAME)" ] ; then $(M_ECHO) "\033[31mSD card name is default, please set SDNAME variable\033[0m" ; $(M_ECHO) ""; exit 1; fi


	$(V)if [ ! "$(OK)" = "1" ] ; then \
	$(M_ECHO) "" ; \
	$(M_ECHO) "\033[1;34mMain installer for Virt2real\033[0m" ; \
	$(M_ECHO) "" ; \
	$(M_ECHO) "\033[31mWARNING!!! Device \033[1m$(SDNAME)\033[0m \033[31mwill be erased! \033[0m" ; \
	$(M_ECHO) "" ; \
	read -p "Press Enter to continue or Ctrl-C to abort" ; \
	fi
	$(ECHO) ""
	$(ECHO) "Ok, next step"
	$(ECHO) ""
	$(V)OK=1



install_bootloader2:: install_intro 
	$(ECHO) ""

	$(V)if [ ! $(SDNAME) ] ; then $(M_ECHO) "\033[31mEmpty SD card name, please set SDNAME variable\033[0m" ; $(M_ECHO) ""; exit 1; fi
	$(V)if [ "$(SDNAME)" == "$(SDDEFNAME)" ] ; then $(M_ECHO) "\033[31mSD card name is default, please set SDNAME variable\033[0m" ; $(M_ECHO) ""; exit 1; fi


	$(V)if [ ! -b $(SDNAME) ] ; then $(M_ECHO) ""; $(M_ECHO) "\033[31mDevice $(SDNAME) not found, aborting\033[0m" ; exit 1; else $(M_ECHO) ""; $(M_ECHO) "\033[32mDevice $(SDNAME) found!\033[0m"; $(M_ECHO) "";  fi
	$(V)if [ ! -f uflash/uflash ] ; then $(M_ECHO) ""; $(M_ECHO) "\033[31muflash error\033[0m"; $(M_ECHO) ""; exit 1; fi
	$(V)if [ ! -f ubl/ubl.bin ] ; then $(M_ECHO) ""; $(M_ECHO) "\033[31mubl error\033[0m"; $(M_ECHO) ""; exit 1; fi
	$(V)if [ ! -f kernel/uImage.bin ] ; then $(M_ECHO) ""; $(M_ECHO) "\033[31muImage error\033[0m"; $(M_ECHO) ""; exit 1; fi
	$(ECHO) ""
	$(ECHO) "\033[1mFlashing bootloader...\033[0m"
	$(V)sudo uflash/uflash -d $(SDNAME) -u ubl/ubl.bin -b kernel/uImage.bin -e 0x82000000 -l 0x82000000 $(OUTPUT)
	sync
	$(ECHO) "";
	$(ECHO) "\033[32m   done\033[0m"
	$(ECHO) ""

prepare_partitions_without_format:: install_intro
	$(ECHO) ""

	$(V)if [ ! $(SDNAME) ] ; then $(M_ECHO) "\033[31mEmpty SD card name, please set SDNAME variable\033[0m" ; $(M_ECHO) ""; exit 1; fi
	$(V)if [ "$(SDNAME)" == "$(SDDEFNAME)" ] ; then $(M_ECHO) "\033[31mSD card name is default, please set SDNAME variable\033[0m" ; $(M_ECHO) ""; exit 1; fi

	$(V)if [ ! -b $(SDNAME) ] ; then $(M_ECHO) "\033[31mDevice $(SDNAME) not found, aborting\033[0m"; exit 1 ; else $(M_ECHO) ""; $(M_ECHO) "\033[32mDevice $(SDNAME) found!\033[0m"; fi
	$(ECHO) ""
	$(ECHO) "\033[1mCreating the partitions on microSD...\033[0m"
	$(V)echo -e "1,5,0xC,*\n6,,L" | sudo sfdisk $(SDNAME) -q -D -H255 -S63 $(OUTPUT)
	$(ECHO) "\033[32m   done\033[0m"
	$(ECHO) ""




clean:
	$(V)make --directory=ubl clean
	$(V)make --directory=kernel clean
