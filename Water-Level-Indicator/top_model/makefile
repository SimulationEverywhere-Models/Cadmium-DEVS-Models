CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I ../../../cadmium/include
INCLUDEDESTIMES=-I ../../../DESTimes/include

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
results_folder := $(shell mkdir -p simulation_results)

#TARGET TO COMPILE MAIN TEST
main_top.o: main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) main.cpp -o build/main_top.o
	
	
simulator: main_top.o
	$(CC) -g -o bin/WLI build/main_top.o

all: simulator

#CLEAN COMMANDS
clean: 
	rm -f bin/* build/*