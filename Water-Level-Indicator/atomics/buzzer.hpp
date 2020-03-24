#ifndef _BUZZER_HPP__
#define _BUZZER_HPP__

//include simulator headers
#include<Cadmium/modeling/ports.hpp>
#include<Cadmium/modeling/message_bag.hpp>

//other header needed for C++ implementation of the model
#include<limits>
#include<math.h>
#include<assert.h>


using namespace cadmium;
using namespace std;

//Port defination
struct buzzer_defs{
	struct buzzIn : public in_port<int>{}; 
	struct buzzOut : public out_port<int>{};
};

//Atomic model class
template<typename TIME> class buzzer {
	
	public:
	using input_ports = tuple<typename buzzer_defs::buzzIn>;
	using output_ports = tuple<typename buzzer_defs::buzzOut>;
	
//State Defination
struct state_type{
	bool transmitting;
	int B;
	int buzzOut;
};
state_type state;

//default constructor without parameters
buzzer()
{
	state.transmitting = false;
	state.B = 0;
	state.buzzOut = 0;
}
//constructor with parameters if needed

// internal transition
void internal_transition(){
	
}

//external transition
void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){
	
	vector<int> bag_port_in;
	bag_port_in = get_messages<typename buzzer_defs::buzzIn>(mbs);
	state.B = bag_port_in[0];
	state.transmitting = true;
	if (state.B == 0){
		state.buzzOut = 1;
	}
	else if (state.B == 3){
		state.buzzOut = 1;
	}
	else{
		state.buzzOut = 0;
	}
}

//confluent transition
void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs){
	internal_transition();
	external_transition(TIME(), std::move(mbs));
}
	
//output function
typename make_message_bags<output_ports>::type output() const { 
	
	typename make_message_bags<output_ports>::type bags;
	if (state.B == 0){
		vector<int> bag_port_out;
		get_messages<typename buzzer_defs::buzzOut>(bags).push_back(state.buzzOut);
	}
	if (state.B == 3){
		vector<int> bag_port_out;
		get_messages<typename buzzer_defs::buzzOut>(bags).push_back(state.buzzOut);
	
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

friend ostringstream& operator<<(ostringstream& os,const typename buzzer<TIME>::state_type& state){
	os<<"buzzOut: "<<state.buzzOut;
	return os;
}
	
};
#endif 
