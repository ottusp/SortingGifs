compileIn:
	gcc -o inputGenerator inputGenerator.c

compileOut:
	gcc -o outputGenerator outputGenerator.c

compile:
	make compileIn
	make compileOut

run:
	make compile
	make in TESTNUMBER=$(TESTNUMBER)
	make out TESTNUMBER=$(TESTNUMBER)

in:
	./inputGenerator $(RANGE) > ../test.in/test$(TESTNUMBER).in

out:
	./outputGenerator $(RANGE) > ../test.out/test$(TESTNUMBER).out

clear:
	rm -f *~ outputGenerator inputGenerator