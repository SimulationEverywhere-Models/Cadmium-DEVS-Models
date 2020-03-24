#ifndef _ADC_HPP__
#define _ADC_HPP__

//include simulator headers
#include<Cadmium/modeling/ports.hpp>
#include<Cadmium/modeling/message_bag.hpp>
#include <cadmium/modeling/dynamic_model.hpp>
#include <cadmium/modeling/dynamic_model_translator.hpp>
#include <cadmium/engine/pdevs_dynamic_runner.hpp>
#include <cadmium/logger/common_loggers.hpp>

//other header needed for C++ implementation of the model
#include <limits>
#include <math.h>
#include <string>
#include <assert.h>


using namespace cadmium;
using namespace std;

//Port defination
struct adc_defs{
	struct SIn : public in_port<int>{};  
	struct DigOut : public out_port<int>{}; 
	struct LevelOut : public out_port<int>{}; 
	struct ToBuzz : public out_port<int>{};
};

//Atomic model class
template<typename TIME> class adc {
	
	public:
	using input_ports = tuple<typename adc_defs::SIn>;
	using output_ports = tuple<typename adc_defs::DigOut, typename adc_defs::LevelOut, typename adc_defs::ToBuzz>;
	
//State Defination
struct state_type{
	int level;
	int digOut;
	int toBuzz;
	bool transmitting;
};
state_type state;

//default constructor without parameters
adc()
{
	
	state.level = 0;
	state.digOut = 0;
	state.toBuzz = 0;
	state.transmitting = false;
}
//constructor with parameters if needed

// internal transition
void internal_transition(){
	
}

//external transition
void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){
	
	vector<int> bag_port_in ;
	
	bag_port_in = get_messages<typename adc_defs::SIn>(mbs);  
	
	
	state.level = bag_port_in[0];
	if ((state.level >=0) && (state.level <=3))
	{
		state.digOut = 0;
		state.toBuzz = 0;
	}
	if ((state.level >=4) && (state.level <= 7))
	{	
		state.digOut = 1;	
	}
	if (state.level >=8 && state.level <= 9)
	{
		state.digOut = 2;
		
	}	
	if ((state.level == 11) ||(state.level == 10))
	{
		state.digOut = 3;
		state.toBuzz = 3;
	}	
	state.transmitting = true;
}

//confluent transition
void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs){
	internal_transition();
	external_transition(TIME(), std::move(mbs));
}
	
//output function
typename make_message_bags<output_ports>::type output() const {
	
	typename make_message_bags<output_ports>::type bags;
	vector<int> bag_port_out1;
	vector<int> bag_port_out2;
	vector<int> bag_port_out3;
	int digOut1 = 0;
	int toBuzz1 = 0;
	
	if (state.level <=11)
	{
	

	get_messages<typename adc_defs::LevelOut>(bags).push_back(state.level);
	
	}
	if ((state.level >=0) && (state.level <=3))
	{
		digOut1 = 0;
		toBuzz1 = 0;
		get_messages<typename adc_defs::DigOut>(bags).push_back(digOut1);
		get_messages<typename adc_defs::ToBuzz>(bags).push_back(toBuzz1);
		
	}
	else if ((state.level >=4) && (state.level <= 7))
	{
		digOut1 = 1;
		get_messages<typename adc_defs::DigOut>(bags).push_back(digOut1);

	}
	else if (state.level >=8 && state.level <= 9)
	{
		digOut1 = 2;
		get_messages<typename adc_defs::DigOut>(bags).push_back(digOut1);

	}
	else if ((state.level == 11) ||(state.level == 10))
	{
		digOut1 = 3;
		toBuzz1 = 3;
		get_messages<typename adc_defs::DigOut>(bags).push_back(digOut1);
		get_messages<typename adc_defs::ToBuzz>(bags).push_back(toBuzz1);
		
	
	}
	return bags;
}	

//time advance function
TIME time_advance() const{
	
	TIME next_interval;
	if(state.transmitting)
	{
		next_interval = TIME("00:00:10:000");
	}
	else{
		next_interval = numeric_limits<TIME>::infinity();
	}
	return next_interval;
}	

friend ostringstream& operator<<(ostringstream& os,const typename adc<TIME>::state_type& i){
os<<"level "<<i.level<<" digout "<<i.digOut;
	return os;
}
	
};
#endif 
