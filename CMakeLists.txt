cmake_minimum_required(VERSION 3.23)
project(Splits)

set(CMAKE_CXX_STANDARD 11)

add_executable(Splits main.cpp Time.cpp SplitSet.cpp Split.cpp SafeSplit.cpp Interface.cpp SplitInterface.cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static")
