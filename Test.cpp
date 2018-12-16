//
// Created by Jan Woźniak on 12/8/2018.
//

#include "Test.h"
#include "SimulatedAnnealing.h"
#include <vector>

void Test::MakeTests() {
    std::vector<std::string> fileNames(
            {/*"Graph_six.txt", "Graph_seven.txt", "Graph_eight.txt", "Graph_nine.txt",*/ "Graph_ten.txt",
                                                                                          "Graph_eleven.txt",
                                                                                          "Graph_twelve.txt",
                                                                                          "Graph_fourteen.txt",
                                                                                          "Graph_fiveteen.txt",
                                                                                          "Graph_sixteen.txt"});
    std::vector<std::string> hmm(
            {"br17.atsp", "ftv33.atsp", "ftv35.atsp",
             "ftv38.atsp", "p43.atsp", "ftv44.atsp", "ftv47.atsp", "ft53.atsp","ftv55.atsp","ftv64.atsp",
             "ft70.atsp",

             "kro124p.atsp", "ftv170.atsp","rbg323.atsp"
             /*"tsp_10.txt", "tsp_12.txt"*/});
    for (auto &fileName : hmm) {
        std::cout << "File name is " << fileName << std::endl;
        CalculateSimulatedAnnealing(1, fileName);
    }
}

void Test::CalculateSimulatedAnnealing(unsigned numberOfTests, std::string fileName) {
    SimulatedAnnealing simulatedAnnealing(true, std::move(fileName));
    std::vector<double> measurements(numberOfTests);
    for (unsigned i = 0; i < numberOfTests; ++i) {
        measurements[i] = simulatedAnnealing.InitAlgorithm(0);
    }
    double average_time = 0;
    for (auto &measurement : measurements) {
        average_time += measurement;
    }
    average_time /= numberOfTests;
    std::cout << "SimulatedAnnealing: " << " ; " << average_time << std::endl;
}
