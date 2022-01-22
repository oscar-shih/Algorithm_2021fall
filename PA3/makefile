CC = g++
CFLAGS = -c -std=c++11 
CCFLAGS = -std=c++11
OPTFLAGS = -O3

all: bin/cb

bin/cb: main.o 
	$(CC) $(CCFLAGS) $(OPTFLAGS) main.o  -o $@

main.o: src/cb.cpp
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

run: bin/cb
	./bin/cb inputs/public_case_1.in outputs/public_case_1.out
	./bin/cb inputs/public_case_2.in outputs/public_case_2.out
	./bin/cb inputs/public_case_3.in outputs/public_case_3.out
	./bin/cb inputs/public_case_4.in outputs/public_case_4.out
	./bin/cb inputs/public_case_7.in outputs/public_case_7.out
	./bin/cb inputs/public_case_8.in outputs/public_case_8.out

clean:
	rm -rf *.o bin/*