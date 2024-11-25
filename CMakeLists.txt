cmake_minimum_required(VERSION 3.27)

project(task_4___5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)


add_executable(ourvolemachine
        Machine.cpp
        Machine.h
        Memory.cpp
        Memory.h
        Register.cpp
        Register.h
        CPU.cpp
        CPU.h
        CU.cpp
        CU.h
        ALU.cpp
        ALU.h
        main.cpp
)

add_executable (test_running
        Memory.cpp
        Memory.h
        Register.cpp
        Register.h
        CU.cpp
        CU.h
        ALU.cpp
        ALU.h
        CPU.cpp
        CPU.h
        Test.cpp
        Test.h
        test_running.cpp
)


add_executable(arbitarylab arbitarylab.cpp)