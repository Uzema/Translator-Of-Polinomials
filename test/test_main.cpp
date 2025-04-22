#include <gtest.h>
#include <iostream>
#include "translator.h"
#include "UI.h"

int main(int argc, char** argv) {
    UserInterface ui;
    while (true) {
        std::string s1, s2;
        std::getline(std::cin, s1);
        ui.process(s1);

        if (s1 == "run_test") {
            ::testing::InitGoogleTest(&argc, argv);
            return RUN_ALL_TESTS();
        }

    }
}