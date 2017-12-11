
# This creates an executable named "go", so after compiling execute via
# 	./go
# First choose what Fortran compiler to use; two options are available for
# FC = fortran compiler.

FC     = gfortran
# FC     = ifort

OPTS   = -O
LINKER = $(FC) 

go: time_example.o elapsedtime.o
	$(LINKER) $(OPTS) -o go time_example.o elapsedtime.o
time_example.o: time_example.f90  elapsedtime.o
	$(FC) $(OPTS) -c time_example.f90
elapsedtime.o: elapsedtime.f90 
	$(FC) $(OPTS) -c elapsedtime.f90

clean:
	rm -f *.o go

