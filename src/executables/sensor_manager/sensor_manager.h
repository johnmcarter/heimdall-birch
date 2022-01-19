#pragma once

/*
 *  Created: 2022/01/18 10:14:50
 *  Last modified: 2022/01/18 22:28:21
 *
 *  Created By : ronin-zero (浪人ー無)
 *  Modified by: John Carter
 */

#include <cstdint>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "sensors/syscall_sensors/syscall_sensor.h"
#include "sensor_observers/syscall_logger.h"
#include "sensor_observers/data_streams/output_stream.h"
#include "daemon_utils/daemonizer.h"

class Sensor_Manager {

    public:
        Sensor_Manager(uint_fast8_t sensor_flags, std::string file_name, 
                        std::string separator, std::string program_name);
        ~Sensor_Manager();

        void run_sensor( bool daemon_on=true );

    private:
        Syscall_Sensor * sensor;
        Syscall_Logger * logger;
        Output_Stream * s_out;

        std::string task_name;

        bool is_running;

        void run_loop( bool daemon_on );
        void handle_pipe();
};
