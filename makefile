#all: task

#task.o: task1.cpp
#	$(CPP) -Wall -I$(INC) -c -o task.o task1.cpp

#task: task.o
#	$(CPP) task.o -L$(LIB) -lmkl_intel -lmkl_core -lmkl_intel_thread -liomp5 -lpthread -lm -o task

CPP=/opt/intel/oneapi/compiler/2021.4.0/linux/bin/icpx
INC=/opt/intel/oneapi/mkl/2021.4.0/include
LIB=/opt/intel/oneapi/mkl/2021.4.0/lib/intel64

all:
	$(CPP) main.cpp init.cpp printAll.cpp CSRform.cpp CSRmulMatrixVector.cpp PermmulMatrix.cpp -L$(LIB) -I$(INC) -o task -qmkl=sequential -w