CC     = g++
OPTS   = -O
LINKER = $(CC) 
INC = -I/usr/include
LIBS = -lrt

go: time_example.o elapsedtime.o
	$(LINKER) $(OPTS) $(INC) $(LIBS) -o go time_example.o elapsedtime.o

time_example.o: time_example.c 
	$(CC) $(OPTS) $(INC) $(LIBS) -c time_example.c

elapsedtime.o: elapsedtime.c 
	$(CC) $(OPTS) $(INC) $(LIBS) -c elapsedtime.c

clean:
	rm -f *.o go

