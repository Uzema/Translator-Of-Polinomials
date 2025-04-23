#include <gtest.h>
#include <iostream>
#include <string>
#include <fstream>
#include "translator.h"
#include "UI.h"

void printFromFile(std::string path, std::string color = "") {
    std::string filename = path;
    std::ifstream inputFile(filename);
    std::string line;
    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    while (std::getline(inputFile, line)) {
        if (color != "") {
            std::cout << color + line + "\033[0m" << std::endl;
            continue;
        }
        std::cout << line << std::endl;
    }
    inputFile.close();
}

int main(int argc, char** argv) {
    UserInterface ui;
    printFromFile("../../polynomials.txt", "\033[31m");
    std::cout << std::endl;
    std::cout << "(Made by Chekotov Alexey and Nikolaev Denis)" << std::endl;
    std::cout << "Write \033[1;32mhelp\033[0m for program usage" << std::endl;
    while (true) {
        std::string s1;
        std::getline(std::cin, s1);
        ui.process(s1);

        if (s1 == "run_test") {
            ::testing::InitGoogleTest(&argc, argv);
            return RUN_ALL_TESTS();
        }
        else if (s1 == "help") {
            std::cout << "This is a help sheet!\n\033[36mrun_test\033[0m - will run gtests" << std::endl;
        }

    }
}