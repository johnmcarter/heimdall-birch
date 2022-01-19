/*
 *  File Name : linux_syscall_record.h
 *  
 *  Creation Date : 05-26-2016
 *  Last modified: 2022/01/18 22:47:07
 *
 *  Created By : ronin-zero (浪人ー無)
 *  Modified by: John Carter
 */

#pragma once

#include <regex>

#include "sensor_observers/data_records/data_record.h"
#include "sensor_observers/data_records/system_call_record.h"
#include "sensor_data/data_patterns/syscall_patterns/linux_syscall_constants.h"
#include "utils/ascii_operations.h"


const uint_fast8_t PROCESS_NAME = 0x80;
const uint_fast8_t PID          = 0x40;
const uint_fast8_t CPU          = 0x20;
const uint_fast8_t TRACE_FLAGS  = 0x10;
const uint_fast8_t TIMESTAMP    = 0x08;
const uint_fast8_t SYSCALL_NUM  = 0x04;
const uint_fast8_t SYSCALL_ARGS = 0x02;

/*
 * At the start of the file "trace"
 * (located at: /sys/kernel/debug/tracing/trace)
 * are 11 lines which appear (more-or-less) as follows.
 * The final line includes 9 '|' characters.  The
 * penultimate line labels each of these with the field
 * of the system call trace that they point to, except
 * for the 4th, 5th, 6th, and 7th '|' which are labeled
 * on lines 5, 6, 7, and 8, respectively (follow the
 * line created by '|', '/', '-' characters to the terminating
 * "=>" for the corresponding label).
 *
 * Some fields (like the timestamp) will change width
 * under certain circumstances (eg. the time requires
 * more digits to display), so we can't treat the index
 * at which the '|' character as found as the start, end,
 * or any consistent offset into the field.
 *
 * However, we CAN be sure that the character at the
 * corresponding index belongs to the field indicated.
 *
 * With that information, we can parse each record by field.
 *
 * For my own convenience, I have labeled their indices
 * after the last line of the example.  I index them
 * beginning at 0.
 *
 * # tracer: nop
 * #
 * # entries-in-buffer/entries-written: 0/15256649   #P:16
 * #
 * #                              _-----=> irqs-off
 * #                             / _----=> need-resched
 * #                            | / _---=> hardirq/softirq
 * #                            || / _--=> preempt-depth
 * #                            ||| /     delay
 * #           TASK-PID   CPU#  ||||    TIMESTAMP  FUNCTION
 * #              | |       |   ||||       |         |
 *               15 17     25  29..32     40        50
 *
 *  They are defined as constants below.
 *
 *  An example of a record found in trace_pipe looks like this:
 *
 *             bash-15509 [002] .... 112170.687012: sys_enter: NR 16 (0, 5403, 7ffd0c9241f0, 0, 0, 700600)
 *
 *  The system call number appears 2 spaces after the function name and the argument list is one space beyond that.
 */

const uint_fast8_t NUM_TFLAGS       = 4; // This is just to avoid magic numbers.  There are 4 flags.

class Linux_Syscall_Record : public Data_Record, public System_Call_Record {

    public:
        
        Linux_Syscall_Record( const std::smatch matches, uint_fast8_t settings_flags=ALL, std::string sep="," );
        ~Linux_Syscall_Record() {}

        std::string get_task() const;
        std::string get_pid() const;
        std::string get_cpu() const;
        std::string get_trace_flags() const;
        std::string get_timestamp() const;
        std::string get_syscall() const;
        std::string get_syscall_args() const;

        uint_fast32_t get_pid_num() const;
        uint_fast32_t get_syscall_num() const;  
        uint_fast16_t get_cpu_num() const;    
        double get_timestamp_num() const;  

    protected:

        virtual std::string get_field( size_t field_num ) const;
        virtual void print( std::ostream& s_out ) const;
};
