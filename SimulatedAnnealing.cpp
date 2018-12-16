//
// Created by Jan Woźniak on 30.11.2018.
//

#include "SimulatedAnnealing.h"
#include "Timer.h"
#include <algorithm>
#include <random>
#include <cmath>

SimulatedAnnealing::SimulatedAnnealing(std::string fileName) : AlgorithmTSP(std::move(fileName)),
                                                               eng(random_device_global()) {
}

SimulatedAnnealing::SimulatedAnnealing(std::string fileName, bool isTsp) : AlgorithmTSP(std::move(fileName), isTsp),
                                                                           eng(random_device_global()) {
}

SimulatedAnnealing::SimulatedAnnealing(bool isTsp, std::string fileName) : AlgorithmTSP(isTsp, std::move(fileName)),
                                                                           eng(random_device_global()) {
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
    double minTemperature = pow(10, -2);
    double temperatureOnTheStep;
    unsigned stepLength = graphSize_*20;
    bestPath = path;
    unsigned lastBestCost = path.cost_;
    unsigned iterationsWithoutChange = 0;

    std::uniform_real_distribution<double> distributionProbability(0.0f, 1.0f);
    unsigned iteration = 0;
    while (temperature_ > minTemperature) {
        temperatureOnTheStep = temperature_;
        for (unsigned inner = 0; inner < stepLength; ++inner) {
            for (unsigned firstIndex = 0; firstIndex < graphSize_ - 1; ++firstIndex) {
                for (unsigned secondIndex = 0; secondIndex < graphSize_ - 1; ++secondIndex) {
                    std::swap(path.path_[firstIndex], path.path_[secondIndex]);
                    CalculatePathCost(path);
                    double probability = (distributionProbability(eng));
                    if (path.cost_ < bestPath.cost_) {
                        bestPath = path;
                    } else if (probability <=
                               1 / (1 + std::exp((path.cost_ - bestPath.cost_) / temperatureOnTheStep))) {
                        bestPath = path;
                    } else {
                        std::swap(path.path_[firstIndex], path.path_[secondIndex]);
                    }
                }
            }
            temperatureOnTheStep *= 0.99;
        }
        if (lastBestCost == bestPath.cost_) {
            ++iterationsWithoutChange;
            if (iterationsWithoutChange == 5) {
                break;
            }
        } else {
            lastBestCost = bestPath.cost_;
        }
        NextTemperature();
        ++iteration;
        if (iteration == 10) {
            std::cout << "Temperatura: " << temperature_ << "; koszt: " << bestPath.cost_ << std::endl;
            iteration = 0;
        }
    }
    std::cout << "Koniec:" << std::endl;
    std::cout << bestPath << std::endl;
}

void SimulatedAnnealing::InitPath(Path &path) {
    for (unsigned i = 0; i < graphSize_ - 1; ++i) {
        path.path_[i] = i + 1;
    }
    CreateShuffledVector(path);
    temperature_ = graphSize_ * (10 ^ 3);
}

unsigned SimulatedAnnealing::CreateShuffledVector(Path &path) {
    CalculatePathCost(path);
    /*Path neighbourPath(path);
    for (unsigned outer = 0; outer < graphSize_; ++outer) {
        for (unsigned firstIndex = 0; firstIndex < graphSize_ - 1; ++firstIndex) {
            for (unsigned secondIndex = 0; secondIndex < graphSize_ - 1; ++secondIndex) {
                std::swap(neighbourPath.path_[firstIndex], neighbourPath.path_[secondIndex]);
                CalculatePathCost(neighbourPath);
                if (neighbourPath.cost_ < path.cost_) {
                    path = neighbourPath;
                } else {
                    std::swap(neighbourPath.path_[firstIndex], neighbourPath.path_[secondIndex]);
                }
            }
        }
    }*/
    return path.cost_;
}

void SimulatedAnnealing::CreatePermutation(Path &path) {
    std::uniform_int_distribution<unsigned> distribution(0, graphSize_ - 2);
    for (unsigned inner = 0; inner < 1; ++inner) {
        std::swap(path.path_[distribution(eng)], path.path_[distribution(eng)]);
    }
    CalculatePathCost(path);
}

void SimulatedAnnealing::NextTemperature() {
    temperature_ *= 0.9;
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
