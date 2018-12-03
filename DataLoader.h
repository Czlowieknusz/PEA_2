//
// Created by Jan Woźniak on 30.11.2018.
//

#ifndef PEA_2_DATALOADER_H
#define PEA_2_DATALOADER_H

#include <fstream>

class DataLoader {
public:
    explicit DataLoader(std::string);

    ~DataLoader();

    unsigned GetGraphSizeFromFile();

    void AddEdgesFromFileToGraph(unsigned **graph, unsigned graphSize);

    unsigned GetUnsignedFromFile();

private:
    std::ifstream myFile_;
    std::string line_of_file_;
};

#endif //PEA_2_DATALOADER_H
