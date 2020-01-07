compile:
	gcc -o unitTest unitTest.c

testOutput:
	../$(SORTINGMETHOD)/$(SORTINGMETHOD) 0 < ./testInAndOut/test.in/test$(TEST).in 

test:
	../$(SORTINGMETHOD)/$(SORTINGMETHOD) 1 < ./testInAndOut/test.in/test$(TEST).in | ./unitTest $(TEST)