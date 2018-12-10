//
// Created by Jan Woźniak on 30.11.2018.
//

#ifndef PEA_2_SIMULATEDANNEALING_H
#define PEA_2_SIMULATEDANNEALING_H

#include "AlgorithmTSP.h"
#include <random>

class SimulatedAnnealing : public AlgorithmTSP {
public:
    explicit SimulatedAnnealing(std::string);

    explicit SimulatedAnnealing(std::string, bool);

    explicit SimulatedAnnealing(bool, std::string);

    double InitAlgorithm(unsigned);

    void CalculatePath(unsigned);

    unsigned CalculateStepLength();

    double CalculateNumberOfSteps(unsigned);

    void InitTemperature(unsigned);

    void InitPath(Path &);

    void CreatePermutation(Path &);

//    const double constValueForCalculatingLength = 2;

    unsigned CreateShuffledVector(Path &);

    void PrintVerticesVector(std::vector<unsigned> &);

    unsigned CalculatePathCost(Path &);

    void NextTemperature();

    const double acceptanceRatio_ = 0.9990;

    double temperature_;

    std::random_device random_device_global;
    std::mt19937_64 eng;
};


#endif //PEA_2_SIMULATEDANNEALING_H
