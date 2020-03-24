//
// Created by Prathmesh Ranaut on 10/18/19.
//

//Cadmium Simulator headers
#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/dynamic_model.hpp>
#include <cadmium/modeling/dynamic_model_translator.hpp>
#include <cadmium/engine/pdevs_dynamic_runner.hpp>
#include <cadmium/logger/common_loggers.hpp>

//Time class header
#include <NDTime.hpp>

//Messages structures
#include "../data_structures/message.hpp"

//Atomic model headers
#include <cadmium/basic_model/pdevs/iestream.hpp> //Atomic model for inputs
#include "../atomics/Authentication.hpp"

//C++ libraries
#include <iostream>
#include <string>

using namespace std;
using namespace cadmium;
using namespace cadmium::basic_models::pdevs;

using TIME = NDTime;

/***** Define input port for coupled models *****/
struct inp : public cadmium::in_port<Message_t>{};

/***** Define output ports for coupled model *****/
struct outp : public cadmium::out_port<Message_t>{};

/****** Input Reader atomic model declaration *******************/
template<typename T>
class InputReader_Message_t : public iestream_input<Message_t,T> {
public:
    InputReader_Message_t () = default;
    InputReader_Message_t (const char* file_path) : iestream_input<Message_t,T>(file_path) {}
};

int main(){

    /****** Input Reader atomic model instantiation *******************/
    const char * i_input_data_control = "../input_data/authentication_input_test.txt";
    shared_ptr<dynamic::modeling::model> input_reader = dynamic::translate::make_dynamic_atomic_model<InputReader_Message_t, TIME, const char* >("input_reader" , std::move(i_input_data_control));

    /****** Authentication atomic model instantiation *******************/
    shared_ptr<dynamic::modeling::model> authentication = dynamic::translate::make_dynamic_atomic_model<Authentication, TIME>("authentication");

    /*******TOP MODEL********/
    dynamic::modeling::Ports iports_TOP = {};
    dynamic::modeling::Ports oports_TOP = {typeid(outp)};
    dynamic::modeling::Models submodels_TOP = {input_reader, authentication};
    dynamic::modeling::EICs eics_TOP = {};
    dynamic::modeling::EOCs eocs_TOP = {
            dynamic::translate::make_EOC<Authentication_defs::out,outp>("authentication")
    };
    dynamic::modeling::ICs ics_TOP = {
            dynamic::translate::make_IC<iestream_input_defs<Message_t>::out,Authentication_defs::in>("input_reader","authentication")
    };
    shared_ptr<dynamic::modeling::coupled<TIME>> TOP;
    TOP = make_shared<dynamic::modeling::coupled<TIME>>(
            "TOP", submodels_TOP, iports_TOP, oports_TOP, eics_TOP, eocs_TOP, ics_TOP
    );

    /*************** Loggers *******************/
    static ofstream out_messages("../simulation_results/authentication_test_output_messages.txt");
    struct oss_sink_messages{
        static ostream& sink(){
            return out_messages;
        }
    };
    static ofstream out_state("../simulation_results/authentication_test_output_state.txt");
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
    r.run_until(NDTime("04:00:00:000"));
    return 0;
}