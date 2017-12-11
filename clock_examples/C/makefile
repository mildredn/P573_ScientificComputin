CC = cc
.PHONEY: clean

go: elapsedtime.o testtime.o
	$(CC) -o go elapsedtime.o testtime.o -L/usr/lib -lrt
elapsedtime.o: elapsedtime.c
	$(CC) -c elapsedtime.c
testtime.o: testtime.c
	$(CC) -c testtime.c
clean:
	rm -f elapsedtime.o testtime.o go
