/*
 *  File Name : sensor_manager.cpp
 *  
 *  Creation Date : 07-08-2016
 *  Last modified: 2022/01/18 22:35:23
 *
 *  Created By : ronin-zero (浪人ー無)
 *  Modified by: John Carter
 */

#include "sensor_manager.h"
#include "utils/constants.h"

Sensor_Manager::Sensor_Manager(uint_fast8_t sensor_flags, std::string file_name, 
                                std::string separator, std::string program_name) {

    sensor = Syscall_Sensor::get_instance();
    task_name = program_name;
    logger = new Syscall_Logger();
    s_out = new Output_Stream( file_name, sensor_flags, separator );
    logger->add_stream( s_out );
    sensor->attach_observer( logger );
}

Sensor_Manager::~Sensor_Manager() {

    delete ( sensor ); 
    delete ( logger );
    delete ( s_out );
}

void Sensor_Manager::run_sensor(bool daemon_on) {

    if ( daemon_on ) {
        Daemonizer::launch_daemon( task_name );
    } else {
        logger->remove_stream( s_out );
        logger->add_stream( new Output_Stream( s_out->get_flags(), s_out->get_separator() ) );
    }

    // We want to start the observing and processing threads before we begin sensing.
    // That way, their thread IDs exist and can get added into the filter.
    // There will be nothing to observe or process, but that should be alright.
    // The processing thread yields if there is no data in the queue.
    //
    // WARNING: As of 4/5/17, this DOES NOT WORK.

    logger->start_observing(); 
    logger->start_processing();
    is_running = ( sensor->start_sensing() & SENSING_ON );
    
    if ( is_running == false) {
        std::cerr << error << "Sensor failed to start" << std::endl;
    } else {
        run_loop( daemon_on );
    }
}

void Sensor_Manager::run_loop( bool daemon_on ){

    while ( is_running == true) {
        if ( daemon_on ) {
            handle_pipe();
        } else {
            string input;

            std::cout << "Enter STOP or stop to stop the sensor." << std::endl;
            std::cin >> input;

            is_running = !( input == "STOP" || input == "stop" || input == "Stop" );
        }
    }
}

void Sensor_Manager::handle_pipe() {
    int32_t fd = open( pipe_name.c_str(), O_RDONLY );
    uint32_t buffsize = 32; // CHECK:  Apologies for magic number.
    char *buf = new char[ buffsize ];

    if ( !read( fd, buf, buffsize ) ) {
        is_running = false;
    } else {
        std::string input( buf );
        is_running = ( input != "STOP" );
        close (fd);
    }

    delete[] buf;
}