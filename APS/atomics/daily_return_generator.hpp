/*
* Guillermo G. Trabes
* ARSLab - Carleton University
*
* Daily Return Generator:
* Cadmium implementation
*/

#ifndef __DAILYRETURNGENERATOR_HPP__
#define __DAILYRETURNGENERATOR_HPP__

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>

#include <limits>
#include <assert.h>
#include <string>
#include <random>
#include <math.h>

#include "../data_structures/time_series.hpp"

using namespace cadmium;
using namespace std;

//Port definition
struct daily_return_generator_defs{
    struct in : public in_port<time_series_element> { };
    struct out : public out_port<time_series_element> { };
};


template<typename TIME> class daily_return_generator{
	public:
	// ports definition
        using input_ports=std::tuple<typename daily_return_generator_defs::in>;
        using output_ports=std::tuple<typename daily_return_generator_defs::out>;

	// state definition
	struct state_type{
		vector<time_series_element> daily_returns_list;
		time_series_element last_element;
		bool output_needed;
    	};

	state_type state;

        // default constructor
        daily_return_generator() {
		state.daily_returns_list = {};
		state.output_needed = 0;
        }

        // internal transition
        void internal_transition() {
		state.output_needed=0;
        }

        // external transition
        void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {

		time_series_element element;

		/* get messages from port*/
		vector<time_series_element> bag_port_in, return_series;

		bag_port_in = get_messages<typename daily_return_generator_defs::in>(mbs);

		/*compute price variation from last price received*/

		if(bag_port_in.size()<2){
			assert(false && "Error: at least two prices are needed to compute a daily return");
		}
		/*if it's the first element there is no previuos value to compute return*/
		state.last_element.price=bag_port_in[0].price;

		/*get the rest of the elements on the bag*/
		for(int i=1;i<bag_port_in.size();i++){

			element.date = bag_port_in[i].date;
			/* calculate daily return */
			element.price = log(bag_port_in[i].price/state.last_element.price);

			/* save element on list */
			state.daily_returns_list.push_back(element);

			/* store price valur to compute next return */
			state.last_element= bag_port_in[i];
		}

		state.output_needed=1;
        }

        // confluence transition
        void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {
            internal_transition();
            external_transition(TIME(), std::move(mbs));
        }

        // output function
        typename make_message_bags<output_ports>::type output() const {
            typename make_message_bags<output_ports>::type bags;

		/* fill bag with return values */
		for(int i=0; i< state.daily_returns_list.size();i++){
			get_messages<typename daily_return_generator_defs::out>(bags).push_back(state.daily_returns_list[i]);
		}

		/* append the last date and price for prediction */
		get_messages<typename daily_return_generator_defs::out>(bags).push_back(state.last_element);

            return bags;
        }

        // time_advance function
        TIME time_advance() const {

		TIME next_internal;
		if (state.output_needed==1) {
			next_internal = TIME("00:00:00:000");
		}else {
			next_internal = numeric_limits<TIME>::infinity();
		}

		return next_internal;
        }

        friend std::ostringstream& operator<<(std::ostringstream& os, const typename daily_return_generator<TIME>::state_type& i) {
        return os;
        }
};
#endif // __SENDER_HPP__
