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
        std::cout << ">>> ";
        std::getline(std::cin, s1);
        try {
            ui.process(s1);
        }
        catch (std::exception const& e) {
            std::cout << "Caught an exception: " << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "Unknown exception" << std::endl;
        }

        if (s1 == "run_test") {
            ::testing::InitGoogleTest(&argc, argv);
            return RUN_ALL_TESTS();
        }
        else if (s1 == "help") {
            std::cout << "This is a help sheet!\n\
You can chose different data structures by using swtich and its full name \nor the short notation in the brackets (case sensitive):\n\
1) SortedTable (st) \n2) UnsortedTable (ut) \n3) BRtree (br) \n4) AVLtree (av) \n5) ChainedHashTable (ht/h1) \n6) ProbingHashTable (ho/h2)\n\n\
You can insert polynoms by using this syntax:\n\
<key> = <your_polynom> (ex. a=16x^2yz)\n\
<key> = <arithmetic expression with already existing polynoms> (ex. a=b+c)\n\
\033[36mrun_test\033[0m - will run gtests\n\
\033[36mswitch\033[0m <name> - will switch data structure(st, ut, av, br, ht, ho)\n\
\033[36mstatus\033[0m - will print current data structure status\n\
\033[36mshow\033[0m - will print out all the stored polynoms along with their keys\n\
\033[36mdel\033[0m <key> - will delete polynom with specified key\n" << std::endl;
        }

    }
}