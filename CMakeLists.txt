cmake_minimum_required(VERSION 3.29)
project(2nd_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(2nd_Project src/main.cpp src/DataLoader.cpp src/DataLoader.h src/TSPSolver.cpp src/TSPSolver.h)
