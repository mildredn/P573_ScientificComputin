include make.inc

# You may need to modify this makefile to include libraries and/or include files for
# things like max() or other utilities. To do that, edit the file make.inc and near
# the bottom define INCS and/or LIBS as needed.

%.o: %.c
	$(CC) $(OPTS) $(INCS) -c $<
%.mod: %.c
	$(CC) $(OPTS) $(INCS) -c $<

go: main.o norm1.o norm2.o norminf.o elapsedtime.o
	$(CC) $(OPTS) $(INCS) -o $@ $^  $(LIBS)

clean:
	rm -f go *.o *.mod 

# Beware: this will also remove the results files.
kleen:
	rm -f go *.o *.mod results