all:
	$(MAKE) -C Chapter01 -f Makefile
	$(MAKE) -C Chapter02 -f Makefile
	$(MAKE) -C Chapter03 -f Makefile
	$(MAKE) -C Chapter04 -f Makefile


clear:
	$(MAKE) -C Chapter01 -f Makefile clear
	$(MAKE) -C Chapter02 -f Makefile clear
	$(MAKE) -C Chapter03 -f Makefile clear	
	$(MAKE) -C Chapter04 -f Makefile clear		