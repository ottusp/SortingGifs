$(MAKE) = make

all:
	make clear
	make compile
	make pallete SORTINGRANGE=$(SORTINGRANGE)
	make steps SORTINGRANGE=$(SORTINGRANGE) SORTINGMETHOD=$(SORTINGMETHOD)
	make gif SORTINGRANGE=$(SORTINGRANGE)

gif:
	./michaelgif $(SORTINGRANGE) < steps$(SORTINGRANGE)

steps:
	rm -f steps*
	$(MAKE) -C ../../sorting/tests/testInAndOut/testMaker/ compileIn
	../../sorting/tests/testInAndOut/testMaker/inputGenerator $(SORTINGRANGE) | ../../sorting/$(SORTINGMETHOD)/$(SORTINGMETHOD) 0 > steps$(SORTINGRANGE)

pallete:
	$(MAKE) -C ../pallete all RANGE=$(SORTINGRANGE)

run:
	make compile
	./michaelgif

compile:
	gcc -o michaelgif ../../gifenc-master/gifenc.c michaelgif.c

clear:
	rm -f steps* *~ michaelgif
	$(MAKE) -C ../pallete clear