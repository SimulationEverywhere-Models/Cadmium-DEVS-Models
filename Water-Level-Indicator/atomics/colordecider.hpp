#ifndef _COLOR_DECIDER_HPP__
#define _COLOR_DECIDER_HPP__

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
struct colordecider_defs{
	struct CDIn1 : public in_port<int>{};  
	struct CDIn2 : public in_port<int>{}; 
	struct CDOut : public out_port<int>{};
	struct L_Out : public out_port<int>{};
};

//Atomic model class
template<typename TIME> class colordecider {
	
	public:
	using input_ports = tuple<typename colordecider_defs::CDIn1, typename colordecider_defs::CDIn2>;
	using output_ports = tuple<typename colordecider_defs::CDOut, typename colordecider_defs::L_Out>;
	
//State Defination
struct state_type{
	bool transmitting;
	int Disp;
	int Clevel;
	int CDOut;
	
};
state_type state;

//default constructor without parameters
adc()
{
	state.transmitting = false;
	state.Disp = 0;
	state.Clevel = 0;
	state.CDOut = 0;
}
//constructor with parameters if needed

// internal transition
void internal_transition(){
	
}

//external transition
void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){
	
	vector<int> bag_port_in1 ;
	vector<int> bag_port_in2 ;
	bag_port_in1 = get_messages<typename colordecider_defs::CDIn1>(mbs);
	bag_port_in2 = get_messages<typename colordecider_defs::CDIn2>(mbs);
	

	state.Disp = (bag_port_in1[0]);
	state.Clevel = (bag_port_in2[0]);
	
	if ((state.Disp ==0)||(state.Disp==3))
	{
		state.CDOut = 1;
	}
	else if (state.Disp ==1)
	{
		state.CDOut = 2;
	}
	else if (state.Disp ==2)
	{
		state.CDOut = 3;
	}	
	else{
		state.CDOut = 0;
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
	
		get_messages<typename colordecider_defs::L_Out>(bags).push_back(state.Clevel);
	
	
	get_messages<typename colordecider_defs::CDOut>(bags).push_back(state.CDOut);
	return bags;
}	

//time advance function
TIME time_advance() const{
	
	TIME next_interval;
	if(state.transmitting)
	{
		next_interval = TIME("00:00:05:000");
	}
	else{
		next_interval = numeric_limits<TIME>::infinity();
	}
	return next_interval;
}	

friend ostringstream& operator<<(ostringstream& os,const typename colordecider<TIME>::state_type& i){
	os<<"CDOut: "<<i.CDOut<<" "<<"L_Out: "<<i.Clevel;
	return os;
}
	
};
#endif 
