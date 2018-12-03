//
// Created by Jan Woźniak on 30.11.2018.
//

#ifndef PEA_2_MENU_H
#define PEA_2_MENU_H

#include <iostream>
#include "SimulatedAnnealing.h"

class Menu {
public:
    explicit Menu(std::string);
    void PrintMainMenu();
    void MainMenu();

    SimulatedAnnealing simulatedAnnealing;
};


#endif //PEA_2_MENU_H
