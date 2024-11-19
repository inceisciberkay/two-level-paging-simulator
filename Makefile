all: src/*.h src/*.c
	gcc src/*.c -o pagesim

runf: pagesim
	./pagesim in1.txt in2.txt 3 out.txt -a 1

runr: pagesim
	./pagesim 20 out.txt -a 1 r 0x00100000 -n 1000

clean:
	rm pagesim out.txt
