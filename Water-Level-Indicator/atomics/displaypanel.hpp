#ifndef _DISPLAY_PANEL_HPP__
#define _DISPLAY_PANEL_HPP__

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
struct displaypanel_defs{
	struct DPIn1 : public in_port<int>{};  
	struct DPIn2 : public in_port<int>{};
	struct greenOut : public out_port<int>{}; 
	struct yellowOut : public out_port<int>{};
	struct redOut : public out_port<int>{};
	struct DPLevel : public out_port<int>{};
};

//Atomic model class
template<typename TIME> class displaypanel {
	
	public:
	using input_ports = tuple<typename displaypanel_defs::DPIn1, typename displaypanel_defs::DPIn2>;
	using output_ports = tuple<typename displaypanel_defs::greenOut, typename displaypanel_defs::yellowOut, typename displaypanel_defs::redOut, typename displaypanel_defs::DPLevel>;
	
//State Defination
struct state_type{
	bool transmitting;
	int Color;
	int D_level;
	int redOut;
	int yellowOut;
	int greenOut;
};
state_type state;

//default constructor without parameters
adc()
{
	state.transmitting = false;
	state.Color = 0;
	state.D_level = 0;
	state.redOut = 0;
	state.yellowOut = 0;
	state.greenOut = 0;
}
//constructor with parameters if needed

// internal transition
void internal_transition(){
	
}

//external transition
void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){ 
	
	
	vector<int> bag_port_in1 ;
	vector<int> bag_port_in2 ;
	bag_port_in1 = get_messages<typename displaypanel_defs::DPIn1>(mbs);
	bag_port_in2 = get_messages<typename displaypanel_defs::DPIn2>(mbs);
	state.Color = bag_port_in1[0];
	state.D_level = bag_port_in2[0];
	if (state.Color == 1)
	{
		state.redOut = 1;
		state.greenOut = 0;
		state.yellowOut = 0;
	}
	if (state.Color == 2)
	{
		state.greenOut = 1;
		state.redOut = 0;
		state.yellowOut = 0;
	}
	if (state.Color == 3)
	{
		state.yellowOut = 1;
		state.greenOut = 0;
		state.redOut = 0;
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
	vector<int> bag_port_out4;

	get_messages<typename displaypanel_defs::DPLevel>(bags).push_back(state.D_level);
	if (state.Color == 1)
	{
	
		get_messages<typename displaypanel_defs::redOut>(bags).push_back(state.redOut);
	}
	if (state.Color == 2)
	{
	
		get_messages<typename displaypanel_defs::greenOut>(bags).push_back(state.greenOut);
	}
	if (state.Color == 3)
	{
		
		get_messages<typename displaypanel_defs::yellowOut>(bags).push_back(state.yellowOut);
	}
	
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

friend ostringstream& operator<<(ostringstream& os,const typename displaypanel<TIME>::state_type& i){
	os<<"Color value: "<<i.Color<<" Red Value: "<<i.redOut<<" Green value: "<<i.greenOut<<" Yellow value: "<<i.yellowOut<<" Level of water: "<<i.D_level;
	return os;
}
	
};
#endif 
