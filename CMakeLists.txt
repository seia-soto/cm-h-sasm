cmake_minimum_required(VERSION 3.19)
project(cmhcpu)

set(CMAKE_CXX_STANDARD 14)

add_executable(cmhcpu main.c main.c lp_utils_debug.c lp_utils_debug.h lp_utils_sio.c lp_utils_sio.h lp_interpreter.c lp_interpreter.h lp_vzheap.c lp_vzheap.h)