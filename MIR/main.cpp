#include <iostream>
#include "gtest/gtest.h"
#include "solucion.h"
#include "auxiliares.h"

int main(int argc, char **argv) {
    std::cout << "Implementando TPI!!" << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}