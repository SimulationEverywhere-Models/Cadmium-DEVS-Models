This folder contains the Water-Level-Indicator DEVS model implemented in Cadmium

/**************************/
/****FILES ORGANIZATION****/
/**************************/

README.txt	
Model description Water-Level-Indicator.doc

atomics [This folder contains atomic models implemented in Cadmium]
	adc.hpp
	buzzer.hpp
	colordecider.hpp
	displaypanel.hpp
bin [This folder will be created automatically the first time you compile the poject.
     It will contain all the executables]
build [This folder will be created automatically the first time you compile the poject.
       It will contain all the build files (.o) generated during compilation]
test [folder for unit testing different atomic models]
	AnalogToDigitalConverter [This folder contains unit test for Analog to Digital Converter atomic model]
		adc.cpp
		adc_input_test.txt	      (Analog to Digital Converter input)
		makefile
	Buzzer	[This folder contains unit test for Buzzer atomic model]
		buzzer.cpp
		buzzer_input_test.txt         (Buzzer Input)
		makefile
	ColorDecider  [This folder contains unit test for Color Decider atomic model]
		colordecider.cpp
		colordecider_input_2_test.txt (Color Decider Input 1)	
		colordecider_input_1_test.txt (Color Decider Input 2)
		makefile
	DisplayPanel  [This folder contains unit test for Display Panel atomic model]
		displaypanel.cpp
		displaypanel_input_2_test.txt (Display Panel Input 1)
		displaypanel_input_1_test.txt (Display Panel Input 2)
		makefile
	
simulation_results [This folder will be created automatically the first time you compile the poject.
                    It will store the outputs from your simulations and tests]
	
top_model [This folder contains the Water-Level-Indicator top model]	
	main.cpp
	wli_input_test.txt	      (Top Model input)
	makefile
	
/*************/
/****STEPS****/
/*************/
****************FOR UNIT Testing AnalogToDigitalConverter(ADC) Atomic model************************

0 - Water-Level-Indicator.doc contains the explanation of this model
1 - Go to directory Water-Level-Indicator\Cadmium-Simulation-Environment\DEVS-Models\Water-Level-Indicator\test\AnalogToDigitalConverter
2 - Compile the project and the tests
	1 - Open the terminal (Cygwin for Windows) in the Water-Level-Indicator\Cadmium-Simulation-Environment\DEVS-Models\Water-Level-Indicator\test\AnalogToDigitalConverter folder
	2 - To compile the project and the tests, type in the terminal:
			make clean; make all
	3 - This will create bin and build folder with ADC_TEST.exe and adc.o extension files.		
3 - Run Model
	1 - Open the terminal in the bin folder Water-Level-Indicator\Cadmium-Simulation-Environment\DEVS-Models\Water-Level-Indicator\test\AnalogToDigitalConverter\bin
	2 - To run the test, type in the terminal "./NAME_OF_THE_COMPILED_FILE" (For windows, "./NAME_OF_THE_COMPILED_FILE.exe"). 
	 i.e. Run ./ADC_TEST
	3 - To check the output of the test, go to the folder simulation_results and open  "adc_test_output_state.txt","adc_test_output_messages.txt". 
4 -  To run the model with different inputs, change input values given in adc_input_test.txt
	
	
******************FOR UNIT Testing Buzzer Atomic model*******************************

0 - Water-Level-Indicator.doc contains the explanation of this model
1 - Go to directory Water-Level-Indicator\Cadmium-Simulation-Environment\DEVS-Models\Water-Level-Indicator\test\Buzzer
2 - Compile the project and the tests
	1 - Open the terminal (Cygwin for Windows) in the Water-Level-Indicator\Cadmium-Simulation-Environment\DEVS-Models\Water-Level-Indicator\test\Buzzer folder
	2 - To compile the project and the tests, type in the terminal:
			make clean; make all
	3 - This will create bin and build folder with BUZZER_TEST.exe and buzzer.o extension files.		
3 - Run Model
	1 - Open the terminal in the bin folder Water-Level-Indicator\Cadmium-Simulation-Environment\DEVS-Models\Water-Level-Indicator\test\Buzzer\bin
	2 - To run the test, type in the terminal "./NAME_OF_THE_COMPILED_FILE" (For windows, "./NAME_OF_THE_COMPILED_FILE.exe"). 
	 i.e. Run ./BUZZER_TEST
	3 - To check the output of the test, go to the folder simulation_results and open  "buzzer_test_output_messages","buzzer_test_output_state". 
4 -  To run the model with different inputs, change input values given in buzzer_input_test.txt	
	

********************FOR UNIT Testing ColorDecider Atomic model**********************************	

0 - Water-Level-Indicator.doc contains the explanation of this model
1 - Go to directory Water-Level-Indicator\Cadmium-Simulation-Environment\DEVS-Models\Water-Level-Indicator\test\ColorDecider
2 - Compile the project and the tests
	1 - Open the terminal (Cygwin for Windows) in the Water-Level-Indicator\Cadmium-Simulation-Environment\DEVS-Models\Water-Level-Indicator\test\ColorDecider folder
	2 - To compile the project and the tests, type in the terminal:
			make clean; make all
	3 - This will create bin and build folder with COLOR_DECIDER_TEST.exe and colordecider.o extension files.		
3 - Run Model
	1 - Open the terminal in the bin folder Water-Level-Indicator\Cadmium-Simulation-Environment\DEVS-Models\Water-Level-Indicator\test\ColorDecider\bin
	2 - To run the test, type in the terminal "./NAME_OF_THE_COMPILED_FILE" (For windows, "./NAME_OF_THE_COMPILED_FILE.exe"). 
	 i.e. Run ./COLOR_DECIDER_TEST
	3 - To check the output of the test, go to the folder simulation_results and open  "colordecider_test_output_messages","colordecider_test_output_state".
4 -  To run the model with different inputs, change input values given in colordecider_input_1_test.txt , colordecider_input_2_test.txt.

*************************FOR UNIT Testing DisplayPanel Atomic model****************************	
	
0 - Water-Level-Indicator.doc contains the explanation of this model
1 - Go to directory Water-Level-Indicator\Cadmium-Simulation-Environment\DEVS-Models\Water-Level-Indicator\test\DisplayPanel
2 - Compile the project and the tests
	1 - Open the terminal (Cygwin for Windows) in the Water-Level-Indicator\Cadmium-Simulation-Environment\DEVS-Models\Water-Level-Indicator\test\DisplayPanel folder
	2 - To compile the project and the tests, type in the terminal:
			make clean; make all
	3 - This will create bin and build folder with DISPLAY_PANEL_TEST.exe and displaypanel.o extension files.		
3 - Run Model
	1 - Open the terminal in the bin folder Water-Level-Indicator\Cadmium-Simulation-Environment\DEVS-Models\Water-Level-Indicator\test\DisplayPanel\bin
	2 - To run the test, type in the terminal "./NAME_OF_THE_COMPILED_FILE" (For windows, "./NAME_OF_THE_COMPILED_FILE.exe"). 
	 i.e. Run ./DISPLAY_PANEL_TEST
	3 - To check the output of the test, go to the folder simulation_results and open  "displaypanel_test_output_messages","displaypanel_test_output_state".
4 -  To run the model with different inputs, change input values given in displaypanel_input_1_test.txt , displaypanel_input_2_test.txt.	

*****************************FOR TESTING TOP-MODEL****************************************
	
0 - Water-Level-Indicator.doc contains the explanation of this model
1 - Go to directory Water-Level-Indicator\Cadmium-Simulation-Environment\DEVS-Models\Water-Level-Indicator\top_model
2 - Compile the project and the tests
	1 - Open the terminal (Cygwin for Windows) in the Water-Level-Indicator\Cadmium-Simulation-Environment\DEVS-Models\Water-Level-Indicator\top_model folder
	2 - To compile the project and the tests, type in the terminal:
			make clean; make all
	3 - This will create bin and build folder with WLI.exe and main_top.o extension files.		
3 - Run Model
	1 - Open the terminal in the bin folder Water-Level-Indicator\Cadmium-Simulation-Environment\DEVS-Models\Water-Level-Indicator\top_model\bin
	2 - To run the test, type in the terminal "./NAME_OF_THE_COMPILED_FILE" (For windows, "./NAME_OF_THE_COMPILED_FILE.exe"). 
	 i.e. Run ./WLI
	3 - To check the output of the test, go to the folder simulation_results and open  "wli_test_output_messages","wli_test_output_state".
4 -  To run the model with different inputs, change input values given in wli_input_test.txt .
	