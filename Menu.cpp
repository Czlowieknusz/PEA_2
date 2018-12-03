//
// Created by Jan Woźniak on 30.11.2018.
//

#include "Menu.h"
#include <iostream>

Menu::Menu(std::string fileName) : simulatedAnnealing(std::move(fileName)) {
    MainMenu();
}

void Menu::PrintMainMenu() {
    std::cout << std::endl << std::endl;
    std::cout << "---------- Main menu ----------" << std::endl;
    std::cout << "1. Print loaded Graph." << std::endl;
    std::cout << "2. Calculate path." << std::endl;
    std::cout << "0. Finish executing program." << std::endl;
}

void Menu::MainMenu() {
    while (true) {
        PrintMainMenu();
        int userOption = -1;
        while (userOption < 0 || userOption > 2) {
            std::cout << "Your option: ";
            std::cin >> userOption;
        }
        switch (userOption) {
            case 0:
                return;
            case 1:
                std::cout << "Printing Graph..." << std::endl;
                simulatedAnnealing.PrintGraph();
                break;
            case 2: {
                unsigned startVertex = 0;
                std::cout << "Which vertex do u want to start from?" << std::endl;
                std::cin >> startVertex;
                simulatedAnnealing.InitAlgorithm(startVertex);
                break;
            }
            default:
                break;
        }
    }
}
