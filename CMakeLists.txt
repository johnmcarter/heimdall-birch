cmake_minimum_required ( VERSION 3.0 )

project (heimdall-birch)

set( SYSCALL_SENSOR_DIR "${CMAKE_SOURCE_DIR}/syscall-sensor" )

add_subdirectory( ${SYSCALL_SENSOR_DIR} )