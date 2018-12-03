//
// Created by Jan Woźniak on 30.11.2018.
//

#include "SimulatedAnnealing.h"
#include "Timer.h"
#include <algorithm>
#include <random>
#include <cmath>

SimulatedAnnealing::SimulatedAnnealing(std::string fileName) : AlgorithmTSP(std::move(fileName)) {
}

double SimulatedAnnealing::InitAlgorithm(unsigned startVertex) {
    Timer timer;
    timer.StartCounter();

    CalculatePath(startVertex);

    double calculatedTime = timer.GetCounter();
    std::cout << "CalculatedTime: " << calculatedTime << std::endl;
    return calculatedTime;
}

unsigned SimulatedAnnealing::CalculateStepLength() {
    return graphSize_ * graphSize_;
}

void SimulatedAnnealing::PrintVerticesVector(std::vector<unsigned> &verticesVec) {
    for (auto vertex : verticesVec) {
        std::cout << vertex << "; ";
    }
    std::cout << std::endl;
}

void SimulatedAnnealing::InitTemperature(unsigned costDelta) {
    temperature_ = costDelta / std::log(acceptanceRatio_);
}

void SimulatedAnnealing::CalculatePath(unsigned startVertex) {
    Path path(startVertex, graphSize_ - 1);
    Path bestPath(startVertex, graphSize_ - 1);
    InitPath(path);
    unsigned numberOfSteps = 100;
    unsigned stepLength = CalculateStepLength();
    bestPath = path;

    std::random_device random_device;
    std::mt19937_64 eng(random_device());
    std::uniform_real_distribution<double> distribution(0.0f, 1.0f);

    std::cout << "Poczatek: " << std::endl;
    std::cout << bestPath << std::endl;
    std::cout << "numberofsteps = " << numberOfSteps << std::endl;
    std::cout << "stepLen = " << stepLength << std::endl;
    // Jest temperatura, jest ilosc stopni, jest dlugosc stopni, jest sciezka, jest najlepsza sciezka
    for (unsigned currentStep = 0; currentStep < numberOfSteps; ++currentStep) {
        for (unsigned inner = 0; inner < stepLength; ++inner) {
            CreatePermutation(path);
//            std::cout << "delta = " << std::exp((-1) * (path.cost_ - bestPath.cost_) / temperature_) << std::endl;
            if (bestPath.cost_ > path.cost_) {
//                std::cout << "Kiedys chyba musi" << std::endl;
                bestPath = path;
            } else if (distribution(eng) <= std::exp((-1) * (path.cost_ - bestPath.cost_) / temperature_)) {
                //                          std::cout << "Hurray!" << std::endl;
                bestPath = path;
            } else {
//                std::cout << "Czy kiedykolwiek?" << std::endl;
            }
        }
//        std::cout << "Temperature: " << temperature_ << "; cost: " << path.cost_ << std::endl;
        // nowa temperatura
        NextTemperature();
    }
    std::cout << "Koniec:" << std::endl;
    std::cout << path << std::endl;

    std::cout << bestPath << std::endl;
}

void SimulatedAnnealing::InitPath(Path &path) {
    for (unsigned i = 0; i < graphSize_ - 1; ++i) {
        path.path_[i] = i + 1;
    }
    unsigned costDelta = CreateShuffledVector(path);
    //InitTemperature(costDelta);
    temperature_ = 1;
    std::cout << "temperature: " << temperature_ << std::endl;
}

unsigned SimulatedAnnealing::CreateShuffledVector(Path &path) {
    std::random_device random_device;
    std::mt19937_64 eng(random_device());
    std::uniform_int_distribution<unsigned> distribution(0, graphSize_ - 2);
    unsigned cost_max = std::numeric_limits<unsigned>::min();
    unsigned cost_min = std::numeric_limits<unsigned>::max();
    unsigned cost_buffer = 0;
    for (unsigned outer = 0; outer < graphSize_; ++outer) {
        for (unsigned inner = 0; inner < 5; ++inner) {
            std::swap(path.path_[distribution(eng)], path.path_[distribution(eng)]);
        }
        cost_buffer = CalculatePathCost(path);
        if (cost_max < cost_buffer) {
            cost_max = cost_buffer;
        }
        if (cost_min > cost_buffer) {
            cost_min = cost_buffer;
        }
    }
    path.cost_ = cost_buffer;
    PrintVerticesVector(path.path_);
    std::cout << "Cost_min = " << cost_min << "; cost_max = " << cost_max << std::endl;
    return (cost_max - cost_min);

}

void SimulatedAnnealing::CreatePermutation(Path &path) {
    std::random_device random_device;
    std::mt19937_64 eng(random_device());
    std::uniform_int_distribution<unsigned> distribution(0, graphSize_ - 2);
    unsigned first = distribution(eng);
    unsigned second = distribution(eng);
    // std::cout << "first: " << first << "; second: " << second << std::endl;
    for (unsigned inner = 0; inner < 1; ++inner) {
        std::swap(path.path_[distribution(eng)], path.path_[distribution(eng)]);
    }
    CalculatePathCost(path);
}

void SimulatedAnnealing::NextTemperature() {
    temperature_ *= 0.95;
}

unsigned SimulatedAnnealing::CalculatePathCost(Path &path) {
    path.cost_ = 0;
    path.cost_ += graph_[path.startVertex_][path.path_[0]];
    unsigned i = 0;
    for (; i < path.path_.size() - 1; ++i) {
        path.cost_ += graph_[path.path_[i]][path.path_[i + 1]];
    }
    path.cost_ += graph_[path.path_[i]][path.startVertex_];
    return path.cost_;
}
