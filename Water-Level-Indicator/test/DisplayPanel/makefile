CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I ../../../../cadmium/include
INCLUDEDESTIMES=-I ../../../../DESTimes/include

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
results_folder := $(shell mkdir -p simulation_results)

#TARGET TO COMPILE 

displaypanel.o: displaypanel.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) displaypanel.cpp -o build/displaypanel.o
	
	
tests: displaypanel.o
		$(CC) -g -o bin/DISPLAY_PANEL_TEST build/displaypanel.o
	
all: tests

#CLEAN COMMANDS
clean: 
	rm -f bin/* build/*