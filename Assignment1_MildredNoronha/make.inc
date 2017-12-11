#-----------------------------------------------------------------------------
# MODIFIED TO ADD LAST LINE TO INCLUDE MATH.H FOR GNU C COMPILER
# Reference : https://stackoverflow.com/questions/42769853/issue-with-makefile-for-including-math-h
# By (un)commenting lines below, can choose between Intel + MKL or GNU + gsl
# Be sure to not mix up those up; changing the compiler requires changing the
# libs and most of the optimizations.
#
# This is primarily set up for Fortran compilation, and chooses options based
# on the Fortran compiler used. However, leave F90=gfortran and it will 
# generally do the right thing. 
#
# Auto variables:
# 	$@ = filename representing target
# 	$% = filename element of an archive 
# 	$< = filename of first prereq
# 	$? = names of all prereqs (space separated) newer than the target
# 	$^ - filenames of all prereqs, no dups
# 	$* = stem of target filename
#
# Append D to get directory part of the value, e.g., $(*D)
#
# For fortran module files:
# 	1. Make the executable dependon the .o file
# 	2. Make the sources that use the module depend on the .mod file
# 	3. On the target line for the module, make both .o and .mod depend on 
# 	the .f90 file., viz.,
# 	kindlytypes.o kindlytypes.mod: kindlytypes.f90
# 		$(F95) -c kindlytypes.f90
#
#------------------------------------
# Started: Mon 12 Sep 2016, 10:20 AM from an earlier version
# Last Modified: Mon 12 Sep 2016, 10:23 AM
#-----------------------------------------------------------------------------

# Prevents attempts to regard all .mod files as modula-2 and using m2c to compile
# them into .c files:
%.o : %.mod 


#===== Compilers =================================================================
CC=gcc
# F90=ifort
F90=gfortran
F95=$(F90)

#===== Optimizations =============================================================
# Some of these are tied to the compiler being Intel. Big fat hairy deal, heh?

# ifeq (F95,"gfortran")       # does not work, even with $(F90) and no ws in F90 
ifeq "$(strip $(F95))" "gfortran"
	OPTS = \
	-O3 \
	-fdiagnostics-color=auto  \
	-Wconversion-extra \
	-fno-range-check		# to allow setting NaN, +/-Inf

	#     -ansi  \
	#     -pedantic  \
	#     -Werror  \
	#     -Wall  \
	#     -W  \
	#     -Wmissing-prototypes  \
	#     -Wstrict-prototypes  \
	#     -Wconversion  \
	#     -Wshadow  \
	#     -Wpointer-arith  \
	#     -Wcast-qual  \
	#     -Wcast-align  \
	#     -Wwrite-strings  \
	#     -Wnested-externs  \
	#     -fshort-enums  \
	#     -fno-common  \
	#     -Dinline=  \
	#     -g  \

else
	OPTS = -O3     \
    -opt-prefetch   \
    -align all      \
    -ftz            \
    -funroll-loops  \
    -pad            \
    -falign-functions=16 \
    -fp-model fast=2 \
    -fp-speculation=fast \
    -opt-prefetch \
    -no-prec-div \
    -xHost \
    # -ccdefault none \

	# -integer-size 64 \
	# -traceback -warn general\
	# -warn all \
	# -openmp 	\				  # For OpenMP-using programs
	# -check arg_temp_created \   # Can be much slower!

endif

CCOPTS = -O3

# use -xAVX in behemoth, or other systems where the cpu supports
# it. I.e., AVX > SSE4.2. When compiling on the machine to execute
# the code, -xHost should take care of that.

#===== Libraries and Other Effluvia ==============================================

# Use the 2013 Intel libs:
# MKLROOT = /opt/intel/composer_xe_2013.3.163/mkl
# LIBS =   -L$(MKLROOT)/lib/intel64 -lmkl_rt -lpthread -lm
# add -lgomp for OpenMP
#---------------------------------------
# For GNU gfortran and GSL: 
# LIBS = -L/usr/lib/ -lgsl -lblas

LIBS += -lm