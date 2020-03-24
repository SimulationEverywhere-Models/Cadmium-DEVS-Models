CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I ../../../../cadmium/include
INCLUDEDESTIMES=-I ../../../../DESTimes/include

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
results_folder := $(shell mkdir -p simulation_results)

#TARGET TO COMPILE

buzzer.o: buzzer.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) buzzer.cpp -o build/buzzer.o

	
tests: buzzer.o
		$(CC) -g -o bin/BUZZER_TEST build/buzzer.o
	
all: tests

#CLEAN COMMANDS
clean: 
	rm -f bin/* build/*