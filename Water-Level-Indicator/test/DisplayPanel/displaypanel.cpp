//Coupled Model
#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/dynamic_model.hpp>
#include <cadmium/modeling/dynamic_model_translator.hpp>
#include <cadmium/engine/pdevs_dynamic_runner.hpp>
#include <cadmium/logger/common_loggers.hpp>

//Time Class header
#include <NDTime.hpp>


//Atomic Model headers
#include <cadmium/basic_model/pdevs/iestream.hpp> //Atomic model for inputs
#include "../../atomics/displaypanel.hpp"

//C++ headers
#include <iostream>
#include <chrono>
#include <algorithm>
#include <string>

using namespace std;
using namespace cadmium ;
using namespace cadmium::basic_models::pdevs;

using TIME = NDTime;

//Define input port for coupled model
struct DPIn1 : public in_port<int>{};
struct DPIn2 : public in_port<int>{};

//Define output port for coupled model
struct greenOut : public out_port<int>{};
struct yellowOut : public out_port<int>{};
struct redOut : public out_port<int>{};
struct DPLevel : public out_port<int>{};

// input reader atomic model declaration
template<typename T> class InputReader_DPIn1 : public iestream_input<int,T>{
	
	public:
		InputReader_DPIn1 () = default;
		InputReader_DPIn1 (const char* file_path) :iestream_input<int,T> (file_path) {}
};  
template<typename T> class InputReader_DPIn2 : public iestream_input<int,T>{
	
	public:
		InputReader_DPIn2 () = default;
		InputReader_DPIn2 (const char* file_path) :iestream_input<int,T> (file_path) {}
};

int main(){

		//Input Reader Atomic model instantation
	const char * i_input_data_1 = "../displaypanel_input_1_test.txt"; 
	
	shared_ptr<dynamic::modeling::model> input_reader_1;
	input_reader_1 = dynamic::translate::make_dynamic_atomic_model<InputReader_DPIn1, TIME, const char*>("input_reader_1",move(i_input_data_1));
	
	const char * i_input_data_2 = "../displaypanel_input_2_test.txt";
	
	shared_ptr<dynamic::modeling::model> input_reader_2;
	input_reader_2 = dynamic::translate::make_dynamic_atomic_model<InputReader_DPIn2, TIME, const char*>("input_reader_2",move(i_input_data_2));
	
	//Display Panel Atomic Model
	shared_ptr<dynamic::modeling::model> displaypanel1;
	displaypanel1 =  dynamic::translate::make_dynamic_atomic_model<displaypanel, TIME>("displaypanel1");
	
	
	//TOP MODEL
	dynamic::modeling::Ports iports_TOP;
	iports_TOP = {typeid(DPIn1),typeid(DPIn2)};
	
	dynamic::modeling::Ports oports_TOP;
	oports_TOP = {typeid(greenOut),typeid(yellowOut),typeid(redOut),typeid(DPLevel)};
	
	dynamic::modeling::Models submodels_TOP;
	submodels_TOP = {input_reader_1, input_reader_2, displaypanel1};
	
	dynamic::modeling::EICs eics_TOP;
	eics_TOP = { 
	};	
	
	dynamic::modeling::EOCs eocs_TOP;
	eocs_TOP = { 
		dynamic::translate::make_EOC<displaypanel_defs::greenOut,greenOut>("displaypanel1"),
		dynamic::translate::make_EOC<displaypanel_defs::yellowOut,yellowOut>("displaypanel1"),
		dynamic::translate::make_EOC<displaypanel_defs::redOut,redOut>("displaypanel1"),
		dynamic::translate::make_EOC<displaypanel_defs::DPLevel,DPLevel>("displaypanel1")
	
	};
	
	dynamic::modeling::ICs ics_TOP;
	ics_TOP = {
		
		dynamic::translate::make_IC<iestream_input_defs<int>::out,displaypanel_defs::DPIn1>("input_reader_1","displaypanel1"),
		dynamic::translate::make_IC<iestream_input_defs<int>::out,displaypanel_defs::DPIn2>("input_reader_2","displaypanel1"),
	};
	
	shared_ptr<dynamic::modeling::coupled<TIME>> TOP;
	
	TOP = make_shared<dynamic::modeling::coupled<TIME>>("TOP",submodels_TOP,iports_TOP,oports_TOP,eics_TOP,eocs_TOP,ics_TOP);
	
	//Loggers
	
	static ofstream out_messages("../simulation_results/displaypanel_test_output_messages.txt"); 
	struct oss_sink_messages{
		static ostream& sink(){   
		return out_messages;
	}
	};
	static ofstream out_state("../simulation_results/displaypanel_test_output_state.txt");
	struct oss_sink_state{
	static ostream& sink(){
	return out_state;
	}
	};
	using state = logger::logger<logger::logger_state, dynamic::logger::formatter<TIME>, oss_sink_state>;
	using log_messages = logger::logger<logger::logger_messages, dynamic::logger::formatter<TIME>, oss_sink_messages>;
	using global_time_mes = logger::logger<logger::logger_global_time, dynamic::logger::formatter<TIME>, oss_sink_messages>;
	using global_time_sta = logger::logger<logger::logger_global_time, dynamic::logger::formatter<TIME>, oss_sink_state>;
	using logger_top = logger::multilogger<state, log_messages, global_time_mes, global_time_sta>;
		
	//Runner
	dynamic::engine::runner<NDTime, logger_top> r(TOP, {0});
	r.run_until(NDTime("04:00:00:000"));
	return 0;
}