cmake_minimum_required(VERSION 3.12)
project(PEA_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(PEA_2 main.cpp Menu.cpp Menu.h AlgorithmTSP.h DataLoader.cpp DataLoader.h SimulatedAnnealing.cpp SimulatedAnnealing.h Timer.cpp Timer.h Test.cpp Test.h)