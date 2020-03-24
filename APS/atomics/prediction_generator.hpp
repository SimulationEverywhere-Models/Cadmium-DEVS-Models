/**
* Guillermo G. Trabes
* ARSLab - Carleton University
*
* Daily Return Generator:
* Cadmium implementation
*/

#ifndef __PREDICTION_GENERATOR_HPP__
#define __PREDICTION_GENERATOR_HPP__

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>

#include <limits>
#include <assert.h>
#include <string>
#include <random>
#include "boost/date_time/gregorian/gregorian.hpp"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random.hpp>

#include "../data_structures/time_series.hpp"

using namespace cadmium;
using namespace std;
using namespace boost::gregorian;

//Port definition
struct prediction_generator_defs{
    struct in : public in_port<time_series_element> { };
    struct out : public out_port<time_series_element> { };
};


template<typename TIME> class prediction_generator{
	public:
	// ports definition
        using input_ports=std::tuple<typename prediction_generator_defs::in>;
        using output_ports=std::tuple<typename prediction_generator_defs::out>;

	// state definition
	struct state_type{
		time_series_element prediction;
		bool output_needed = 0;
    	};

	state_type state;

	/* random generation auxiliar function*/
        boost::random::mt19937 gen;


        // default constructor
        prediction_generator() {
		gen.seed(std::time(0));
        }

        // internal transition
        void internal_transition() {
		state.output_needed=0;
        }

        // external transition
        void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {

		time_series_element random_value, last_value;
		date d;
		double normal_value;
		/* get messages from port*/
		vector<time_series_element> bag_port_in;

		bag_port_in = get_messages<typename prediction_generator_defs::in>(mbs);

		/* get random value */
		random_value= bag_port_in[0];

		/* get last date and price */
		last_value= bag_port_in[1];


		/* convert string to boost date datatype */
		d = from_simple_string(last_value.date);

		/* advenace date on day for prediction */
	 	d += days(1);

		/* convert back to string and store in state*/
		state.prediction.date = to_iso_extended_string(d);


		/* create normal distribution (0,1) */
	        boost::random::normal_distribution<> nd(0.0, 1.0);

		boost::variate_generator<boost::mt19937&, 
                           boost::normal_distribution<> > var_nor(gen, nd);

		/* calculate normal value */
		normal_value = var_nor();

		/* calculate prediction */
		state.prediction.price = last_value.price+exp(random_value.price*normal_value);

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

	    get_messages<typename prediction_generator_defs::out>(bags).push_back(state.prediction);

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

        friend std::ostringstream& operator<<(std::ostringstream& os, const typename prediction_generator<TIME>::state_type& i) {
        return os;
        }
};
#endif // __PREDICTION_GENERATOR_HPP__
