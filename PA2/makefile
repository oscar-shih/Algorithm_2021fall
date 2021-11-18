CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
OPTFLAGS = -O3

all	: bin/mps

bin/mps	: mps_opt.o
			$(CC) $(OPTFLAGS)  mps_opt.o -o bin/mps
mps_opt.o : src/mps.cpp 
			$(CC) $(CFLAGS) $< -o $@
run: bin/mps
	./bin/mps inputs/12.in outputs/12.out
	./bin/mps inputs/1000.in outputs/1000.out
	./bin/mps inputs/10000.in outputs/10000.out
	./bin/mps inputs/100000.in outputs/100000.out

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*