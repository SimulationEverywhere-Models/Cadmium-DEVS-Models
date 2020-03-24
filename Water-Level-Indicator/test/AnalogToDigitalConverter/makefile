CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I ../../../../cadmium/include
INCLUDEDESTIMES=-I ../../../../DESTimes/include

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
results_folder := $(shell mkdir -p simulation_results)

#TARGET TO COMPILE

adc.o: adc.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) adc.cpp -o build/adc.o
	
	
tests: adc.o
		$(CC) -g -o bin/ADC_TEST build/adc.o

all: tests

#CLEAN COMMANDS
clean: 
	rm -f bin/* build/*