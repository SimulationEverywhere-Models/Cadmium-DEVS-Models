CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I ../../cadmium/include
INCLUDEDESTIMES=-I ../../DESTimes/include

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
results_folder := $(shell mkdir -p simulation_results)

#TARGET TO COMPILE ALL THE TESTS TOGETHER (NOT SIMULATOR)
time_series.o: data_structures/time_series.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) data_structures/time_series.cpp -o build/time_series.o

main_top.o: top_model/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) top_model/main.cpp -o build/main_top.o -lboost_date_time

main_bootstrap_generator_test.o: test/main_bootstrap_generator_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) test/main_bootstrap_generator_test.cpp -o build/main_bootstrap_generator_test.o -lboost_date_time
	
main_daily_return_generator_test.o: test/main_daily_return_generator_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) test/main_daily_return_generator_test.cpp -o build/main_daily_return_generator_test.o

main_random_selector_test.o: test/main_random_selector_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) test/main_random_selector_test.cpp -o build/main_random_selector_test.o

main_prediction_generator_test.o: test/main_prediction_generator_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) test/main_prediction_generator_test.cpp -o build/main_prediction_generator_test.o -lboost_date_time

tests: main_daily_return_generator_test.o main_random_selector_test.o main_prediction_generator_test.o main_bootstrap_generator_test.o time_series.o
		$(CC) -g -o bin/DAILY_RETURN_GENERATOR_TEST build/main_daily_return_generator_test.o build/time_series.o
		$(CC) -g -o bin/RANDOM_SELECTOR_TEST build/main_random_selector_test.o build/time_series.o
		$(CC) -g -o bin/PREDICTION_GENERATOR_TEST build/main_prediction_generator_test.o build/time_series.o -lboost_date_time  
		$(CC) -g -o bin/BOOTSTRAP_GENERATOR_TEST build/main_bootstrap_generator_test.o build/time_series.o -lboost_date_time

#TARGET TO COMPILE ONLY APS SIMULATOR
simulator: main_top.o time_series.o
	$(CC) -g -o bin/APS build/main_top.o build/time_series.o -lboost_date_time
	
#TARGET TO COMPILE EVERYTHING (ABP SIMULATOR + TESTS TOGETHER)
all: simulator tests

#CLEAN COMMANDS
clean: 
	rm -f bin/* build/*
