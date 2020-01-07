all:
	make compile
	make txt

compile:
	gcc -o pallete makepallete.c -lm

txt:
	./pallete $(RANGE)

clear:
	rm -f pallete pallete.txt