CC     = g++
OPTS   = -O
LINKER = $(CC) 
INC = -I/usr/include
LIBS = -lrt

go: example_getr.o getr.o
	$(LINKER) $(OPTS) $(INC) $(LIBS) -o go example_getr.o getr.o

example_getr.o: example_getr.c 
	$(CC) $(OPTS) $(INC) $(LIBS) -c example_getr.c

getr.o: getr.c 
	$(CC) $(OPTS) $(INC) $(LIBS) -c getr.c

clean:
	rm -f *.o go 

