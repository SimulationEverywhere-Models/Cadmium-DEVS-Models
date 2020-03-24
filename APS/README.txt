This folder contains the ASSET PRICE SIMULATOR DEVS model implemented in Cadmium

/**************************/
/****FILES ORGANIZATION****/
/**************************/

README.txt	
APS.doc
makefile
APSModelDescription.xml

atomics [This folder contains atomic models implemented in Cadmium]
	daily_return_generator.hpp
	random_selector.hpp
	prediction_generator.hpp
bin [This folder will be created automatically the first time you compile the poject.
     It will contain all the executables]
build [This folder will be created automatically the first time you compile the poject.
       It will contain all the build files (.o) generated during compilation]
data_structures [This folder contains message data structure used in the model]
	time_series.hpp
	time_series.cpp
input_data [This folder contains all the input data to run the model and the tests]
	daily_return_generator_input_test1.txt
	daily_return_generator_input_test2.txt
	random_selector_input_test1.txt
	random_selector_input_test2.txt
	prediction_generator_input_test1.txt
	prediction_generator_input_test2.txt
	bootstrap_generator_input_test1.txt
	bootstrap_generator_input_test2.txt
	APS_input_test.txt
simulation_results [This folder will be created automatically the first time you compile the poject.
                    It will store the outputs from your simulations and tests]
test [This folder the unit test of the atomic models]
	main_daily_return_generator_test.cpp
	main_random_selector_test.cpp
	main_prediction_generator_test.cpp
	main_bootstrap_generator_test.cpp
top_model [This folder contains the Asset Price Simulator top model]	
	main.cpp
scripts
	[This folder contains the scripts to execute the bin files with the different input_data files]
	APS.sh [executes APS file (compiled in the bin folder) with the APS_input_test.txt input data file]
	bootstrap_generator_test1.sh [executes BOOTSTRAP_GENERATOR_TEST file (compiled in the bin folder) with the bootstrap_generator_input_test1.txt input data file]
	bootstrap_generator_test2.sh [executes BOOTSTRAP_GENERATOR_TEST file (compiled in the bin folder) with the bootstrap_generator_input_test2.txt input data file]
	daily_return_generator_test1.sh [executes DAILY_RETURN_GENERATOR_TEST file (compiled in the bin folder) with the daily_return_generator_input_test1.txt input data file]
	daily_return_generator_test2.sh [executes DAILY_RETURN_GENERATOR_TEST file (compiled in the bin folder) with the daily_return_generator_input_test2.txt input data file]
	prediction_generator_test1.sh [executes PREDICTION_GENERATOR_TEST file (compiled in the bin folder) with the prediction_generator_input_test1.txt input data file]
	prediction_generator_test2.sh [executes PREDICTION_GENERATOR_TEST file (compiled in the bin folder) with the prediction_generator_input_test2.txt input data file]	
	random_selector_test1.sh [executes RANDOM_SELECTOR_TEST file (compiled in the bin folder) with the random_selector_input_test2.txt input data file]
	random_selector_test2.sh [executes RANDOM_SELECTOR_TEST file (compiled in the bin folder) with the random_selector_input_test2.txt input data file]

/*************/
/****STEPS****/
/*************/

0 - APS.doc contains the explanation of this model

1 - Update include path in the makefile in this folder and subfolders. You need to update the following lines:
	INCLUDECADMIUM=-I ../../cadmium/include
	INCLUDEDESTIMES=-I ../../DESTimes/include
    Update the relative path to cadmium/include from the folder where the makefile is. You need to take into account where you copied the folder during the installation process
	Example: INCLUDECADMIUM=-I ../../cadmium/include
	Do the same for the DESTimes library
    NOTE: if you follow the step by step installation guide you will not need to update these paths.

2 - Compile the project and the tests
	1 - Open the terminal (Ubuntu terminal for Linux and Cygwin for Windows) in the APS folder
	2 - To compile the project and the tests, type in the terminal:
			make clean; make all
3 - Run tests
	1 - Open the terminal in the scripts folder.
	2 - To run the test, type in the terminal "./NAME_OF_THE_SCRIPT.sh" (For windows, inside the script the executable should be changed to the extension .exe).
	3 - To check the output of the test, go to the folder simulation_results.
			
4 - Run the top model
	1 - Open the terminal (Ubuntu terminal for Linux and Cygwin for Windows) in the scripts folder.
	2 - To run the model, type in the terminal "./APS.sh" (For windows, inside the script the executable should be changed to the extension .exe).
	3 - To check the output of the model, go to the folder simulation_results and open "APS_output_messages.txt".






