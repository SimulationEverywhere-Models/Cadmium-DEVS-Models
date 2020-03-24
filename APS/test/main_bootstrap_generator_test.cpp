//Cadmium Simulator headers
#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/dynamic_model.hpp>
#include <cadmium/modeling/dynamic_model_translator.hpp>
#include <cadmium/engine/pdevs_dynamic_runner.hpp>
#include <cadmium/logger/common_loggers.hpp>


#include "boost/date_time/gregorian/gregorian.hpp"

//Time class header
#include <NDTime.hpp>

//Times series data - date and price
#include "../data_structures/time_series.hpp"


//Atomic model headers
#include <cadmium/basic_model/pdevs/iestream.hpp> //Atomic model for inputs
#include "../atomics/random_selector.hpp"
#include "../atomics/prediction_generator.hpp"


//C++ headers
#include <iostream>
#include <chrono>
#include <algorithm>
#include <string>


using namespace std;
using namespace cadmium;
using namespace cadmium::basic_models::pdevs;

using TIME = NDTime;

/***** Define input port for coupled models *****/
struct bg_input1 : public in_port<time_series_element>{};
/***** Define output ports for coupled model *****/
struct bg_output1 : public out_port<time_series_element>{};


/***** Define output ports for coupled model *****/
struct top_out : public out_port<time_series_element>{};



/****** Input Reader atomic model declaration *******************/
template<typename T>
class InputReader_time_series_t : public iestream_input<time_series_element,T> {
public:
    InputReader_time_series_t() = default;
    InputReader_time_series_t(const char* file_path) : iestream_input<time_series_element,T>(file_path) {}
};



int main(int argc, char ** argv) {

    if (argc < 2) {
        cout << "Program used with wrong parameters. The program must be invoked as follow:";
        cout << argv[0] << " path to the input file " << endl;
        return 1; 
    }
    /****** Input Reader atomic model instantiation *******************/
    string input = argv[1];
    const char * i_input = input.c_str();
    shared_ptr<dynamic::modeling::model> input_reader = dynamic::translate::make_dynamic_atomic_model<InputReader_time_series_t, TIME, const char* >("input_reader" , move(i_input));

    /****** random_selector model instantiation *******************/
    shared_ptr<dynamic::modeling::model> random_selector1 = dynamic::translate::make_dynamic_atomic_model<random_selector, TIME>("random_selector1");

    /****** daily_prediction_generator atomic model instantiation *******************/
    shared_ptr<dynamic::modeling::model> prediction_generator1 = dynamic::translate::make_dynamic_atomic_model<prediction_generator, TIME>("prediction_generator1");


    /*******BOOSTRAP GENERATOR COUPLED MODEL********/
    dynamic::modeling::Ports iports_bg = {typeid(bg_input1)};
    dynamic::modeling::Ports oports_bg = {typeid(bg_output1)};
    dynamic::modeling::Models submodels_bg = {random_selector1, prediction_generator1};
    dynamic::modeling::EICs eics_bg = {
        dynamic::translate::make_EIC<bg_input1, random_selector_defs::in>("random_selector1")
    };
    dynamic::modeling::EOCs eocs_bg = {
        dynamic::translate::make_EOC<prediction_generator_defs::out, bg_output1>("prediction_generator1")
    };
    dynamic::modeling::ICs ics_bg = {
        dynamic::translate::make_IC<random_selector_defs::out, prediction_generator_defs::in>("random_selector1","prediction_generator1"),
    };
    shared_ptr<dynamic::modeling::coupled<TIME>> bootstrap_generator;
    bootstrap_generator = make_shared<dynamic::modeling::coupled<TIME>>(
        "bootstrap_generator", submodels_bg, iports_bg, oports_bg, eics_bg, eocs_bg, ics_bg
    );



    /*******TOP COUPLED MODEL********/
    dynamic::modeling::Ports iports_TOP = {};
    dynamic::modeling::Ports oports_TOP = {typeid(top_out)};


    dynamic::modeling::Models submodels_TOP = {input_reader, bootstrap_generator};


    dynamic::modeling::EICs eics_TOP = {};
    dynamic::modeling::EOCs eocs_TOP = {
        dynamic::translate::make_EOC<bg_output1,top_out>("bootstrap_generator")
    };

    dynamic::modeling::ICs ics_TOP = {
        dynamic::translate::make_IC<iestream_input_defs<time_series_element>::out, bg_input1>("input_reader","bootstrap_generator")
    };



    shared_ptr<cadmium::dynamic::modeling::coupled<TIME>> TOP;

    TOP = make_shared<dynamic::modeling::coupled<TIME>>(
        "TOP", submodels_TOP, iports_TOP, oports_TOP, eics_TOP, eocs_TOP, ics_TOP 
    );

    /*************** Loggers *******************/
    static ofstream out_messages("../simulation_results/bootstrap_generator_output_messages.txt");
    struct oss_sink_messages{
        static ostream& sink(){          
            return out_messages;
        }
    };
    static ofstream out_state("../simulation_results/bootstrap_generator_output_state.txt");
    struct oss_sink_state{
        static ostream& sink(){          
            return out_state;
        }
    };
    
    using state=logger::logger<logger::logger_state, dynamic::logger::formatter<TIME>, oss_sink_state>;
    using log_messages=logger::logger<logger::logger_messages, dynamic::logger::formatter<TIME>, oss_sink_messages>;
    using global_time_mes=logger::logger<logger::logger_global_time, dynamic::logger::formatter<TIME>, oss_sink_messages>;
    using global_time_sta=logger::logger<logger::logger_global_time, dynamic::logger::formatter<TIME>, oss_sink_state>;

    using logger_top=logger::multilogger<state, log_messages, global_time_mes, global_time_sta>;

    /************** Runner call ************************/ 
    dynamic::engine::runner<NDTime, logger_top> r(TOP, {0});
    r.run_until_passivate();
    return 0;
}
