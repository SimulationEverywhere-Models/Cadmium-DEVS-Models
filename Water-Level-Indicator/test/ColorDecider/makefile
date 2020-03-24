CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I ../../../../cadmium/include
INCLUDEDESTIMES=-I ../../../../DESTimes/include

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
results_folder := $(shell mkdir -p simulation_results)

#TARGET TO COMPILE

colordecider.o: colordecider.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) colordecider.cpp -o build/colordecider.o
	
	
tests: colordecider.o
		$(CC) -g -o bin/COLOR_DECIDER_TEST build/colordecider.o

all: tests

#CLEAN COMMANDS
clean: 
	rm -f bin/* build/*