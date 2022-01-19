/*
 *  File Name : system_call_record.h
 *  
 *  Creation Date : 12-23-2016
 *
 *  Last Modified : Tue 11 Dec 2018 06:13:40 AM EST
 *
 *  Created By : ronin-zero (浪人ー無)
 *
 */

#pragma once

#include <cstdint>

class System_Call_Record {

    public:
       virtual uint_fast32_t get_pid_num() const = 0;
       virtual uint_fast32_t get_syscall_num() const = 0;   
};
