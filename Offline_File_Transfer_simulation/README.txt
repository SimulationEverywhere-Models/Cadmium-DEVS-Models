README.txt

This folder contains the OFFLINE FILE TRANSFER DEVS model implemented in Cadmium

/**************************/
/****FILES ORGANIZATION****/
/**************************/

README.txt	
OfflineFileTransferSimulation.doc
OFT.xml
DEVSModelForm

makefile

atomics [This folder contains atomic models implemented in Cadmium]
	FileServerSender.hpp
	FileServerReceiver.hpp	
	receiver.hpp
	sender.hpp
	subnet.hpp
bin [This folder will be created automatically the first time you compile the poject.
     It will contain all the executables]
build [This folder will be created automatically the first time you compile the poject.
       It will contain all the build files (.o) generated during compilation]
data_structures [This folder contains message data structure used in the model]
	message.hpp
	message.cpp
input_data [This folder contains all the input data to run the model and the tests]
	controlIn.txt -----------> contains negative/zero/positive inputs.
	fileserver_receiver_ackIn_test.txt -----> input values to simulate ack that comes in from FileServerSender 
	fileserver_receiver_dataIn_test.txt ----> input values to simulate File that comes in from AccessNetworkA 
	fileserversender_ackIn_test.txt --------> input values to simulate ack that comes in from receiver 
	fileserversender_dataIn_test.txt -------> input values to simulate the File that comes in from FileServerReceiver
	fileserversender_requestIn_test.txt ----> input values to simulate the requestIn 
	receiver_input_test.txt ----------------> input values to simulate File that comes from AccessNetworkB
	sender_input_test_ack_In.txt------------> input values to simulate ack that comes from AccessNetworkA
	sender_input_test_control_In.txt--------> Contains positive/negative/zero values of ControlIn.
	subnet_input_test.txt-------------------> input values to simulate data incoming from the Sender or Receiver
	requestIn.txt -----------> Contains positive values of requestIn.
	NoRequest.txt -----------> Contains zero values for requestIn.

simulation_results [It will store the outputs from simulations and tests. Output logs of all the test scenarios are present here]

	OfflineFT_output_messages.txt ------> Messages Output of the Main Model
	OfflineFT_output_state.txt ---------> State Output of the Main Model
	OfflineFT_output_messages_reqIn.txt ------> Messages Output of the Main Model when the requestIn values are positive
	OfflineFT_output_state_reqIn.txt ---------> State Outputs of the Main Model when the requestIn values are positive
	OfflineFT_output_messages_NoRequest.txt ------> Messages Output of the Main Model when the requestIn values are zero
	OfflineFT_output_state_NoRequest.txt ---------> State Outputs of the Main Model when the requestIn values are zero
	FileServerReceiver_test_output_messages.txt ----> Output of FileServerReceiver atomic model
	FileServerReceiver_test_output_state.txt -------> Output of FileServerReceiver atomic model
	FileServerSender_test_output_messages_requestIn.txt ----> Message Output of FileServerSender atomic model when there are positive values of requestIn
	FileServerSender_test_output_state_requestIn.txt ----> State Output of FileServerSender atomic model when there are positive requestIn
	FileServerSender_test_output_messages_NoRequest.txt ----> Message Output of FileServerSender atomic model when requestIn is zero
	FileServerSender_test_output_state_NoRequest.txt ----> State Output of FileServerSender atomic model when requestIn is zero
	FileServerSender_test_output_messages.txt ------> Output of FileServerSender atomic model
	FileServerSender_test_output_state.txt ------> Output of FileServerSender atomic model
	sender_test_output_messages.txt ---------> Message Output of sender atomic model
	sender_test_output_state.txt ----------> State Output of sender atomic model
	receiver_test_output_message.txt ------> Message Output of receiver atomic model
	receiver_test_output_state.txt --------> State Output of receiver atomic model
	subnet_test_output_message.txt --------> Message Output of subnet test model
	subnet_test_output_state.txt ----------> State Output of subnet test model

test [This folder the unit test of the atomic models]
	main_fileserversender_test.cpp
	main_fileserverreceiver_test.cpp	
	main_receiver_test.cpp
	main_sender_test.cpp
	main_subnet_test.cpp
top_model [This folder contains the Offline_File_transfer_Simulation top model]	
	main.cpp
	
/*************/
/****STEPS****/
/*************/

0 - OfflineFileTransferSimulation.doc contains the explanation of this model

1 - Update include path in the makefile in this folder and subfolders. following lines need to be updated:
	INCLUDECADMIUM=-I ../../cadmium/include
	INCLUDEDESTIMES=-I ../../DESTimes/include
    	Update the relative path to cadmium/include from the folder where the makefile is. You need to take into account where you copied the folder during the installation process
	Example: INCLUDECADMIUM=-I ../../cadmium/include
	Do the same for the DESTimes library
   
2 - Compile the project and the tests
	2.1 - Open the terminal (Ubuntu terminal for Linux) in the Offline_File_Transfer_Simulation folder
	2.2 - To compile the project and the tests, type in the terminal:
		make clean; make all
3 - Running Simulation tests.
	3.1 - Open the terminal and cd to scripts folder. 
	3.2 - To run the test, first we give permission to the scripts to run: type in the terminal "chmod 777 *.sh" 
	  3.2.1--For the Test Scenario for Main Model when there is a download request (Positive Request Input) and different values of controlIn.
		./Main_Model_Positive_Request.sh
		--Please rename the output files before running the next test to retain the output of this test case ("offlineFT_output_messages.txt", offlineFT_output_state.txt) 
	  3.2.2--For the Test Scenario for Main Model when there is no download request (Zero Request Input) and different values of controlIn.
		./Main_Model_Zero_Request.sh

	  3.2.3--For the Test Scenario for FileServerSender atomic model when there is no download request (Zero Request Input)
		./FileServerSender_zero_request.sh
		--Please rename the output files before running the next test to retain the output of this test case ("FileServerSender_test_output_messages.txt", 		 FileServerSender_test_output_state.txt) 
	  3.2.4--For the Test Scenario for FileServerSender atomic model when there is a download request (Positive Request Input)
		./FileServerSender_Positive_request.sh

	  3.2.5--For testing the FileServerReceiver atomic model
		./FileServerReceiver_test.sh
	  3.2.6--For testing the Receiver atomic model
		./Receiver_test.sh
	  3.2.7--For testing the Subnet atomic model
		./Subnet_test.sh
	  3.2.8--For the Test Scenario for Sender atomic model with controlIn positive or negative indicating packet sent or not sent respectively.
		./Sender_test.sh
		
4 - To check the output of the test, go to the folder simulation_results and open the output files for all the test cases run. For example, for FileServerSender atomic model, 		"FileServerSender_test_output_messages.txt" and "FileServerSender_test_output_state.txt" would be generated. These files need to be renamed after each test run because it will 	be overwritten on every subsequent test run.



