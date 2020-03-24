/**
* Guillermo G. Trabes
* ARSLab - Carleton University
*
* Daily Return Generator:
* Cadmium implementation
*/

#ifndef __RANDOM_SELECTOR_HPP__
#define __RANDOM_SELECTOR_HPP__

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>

#include <limits>
#include <assert.h>
#include <string>
#include <random>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>


#include "../data_structures/time_series.hpp"

using namespace cadmium;
using namespace std;


//Port definition
struct random_selector_defs{
    struct in : public in_port<time_series_element> { };
    struct out : public out_port<time_series_element> { };
};


template<typename TIME> class random_selector{
	public:
	// ports definition
        using input_ports=std::tuple<typename random_selector_defs::in>;
        using output_ports=std::tuple<typename random_selector_defs::out>;

	// state definition
	struct state_type{
		time_series_element last_element, random_choice;
		int output_needed;
    	};

	/* state declaration */
	state_type state;

	/* random generation auxiliar function*/
	boost::random::mt19937 gen;


        // default constructor
        random_selector() {
	  state.output_needed = 0;
	  gen.seed(std::time(0));
        }

        // internal transition
        void internal_transition() {
		state.output_needed=0;
        }

        // external transition
        void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {

		int limit, random_index;

		/* get messages from port*/
		vector<time_series_element> bag_port_in;

		bag_port_in = get_messages<typename random_selector_defs::in>(mbs);

		/* calculate limit on the value to choose random value*/
		limit=bag_port_in.size()-2;

		/* pick random value */

		/* generate integer random uniform distribution */
		boost::random::uniform_int_distribution<> index(0, limit);

		/* get random index */
		random_index = index(gen);

                /*store random value and last price on state*/
		state.random_choice = bag_port_in[random_index];
		state.last_element = bag_port_in[bag_port_in.size()-1];

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

	    get_messages<typename random_selector_defs::out>(bags).push_back(state.random_choice);
	    get_messages<typename random_selector_defs::out>(bags).push_back(state.last_element);

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

        friend std::ostringstream& operator<<(std::ostringstream& os, const typename random_selector<TIME>::state_type& i) {
            os << "Random choice: " << i.random_choice.date << " " << i.random_choice.price << " " << "Last element: " << i.last_element.date << " " << i.last_element.price;
        return os;
        }
};
#endif // __RANDOM_SELECTOR_HPP__

