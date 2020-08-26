#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(formatoValidoTEST, longitudErronea){
    audio a = {1,2,3,4,5};
    int canal = 3;
    int profundidad = 4;

    EXPECT_FALSE(formatoValido(a, canal, profundidad));
}

TEST(formatoValidoTEST, audioVacio){
    audio a = {};
    int canal = 2;
    int profundidad = 3;

    EXPECT_FALSE(formatoValido(a, canal, profundidad));
}

TEST(formatoValidoTEST,noEstaEnProfundidadPorArriba){
    audio a = {-6,1,3,-3,8,0};
    int canal = 2;
    int profundidad = 4;

    EXPECT_FALSE(formatoValido(a, canal, profundidad));
}
TEST(formatoValidoTEST,noEstaEnProfundidadPorAbajo){
    audio a = {-9,1,7,-2,5,3};
    int canal = 2;
    int profundidad = 4;

    EXPECT_FALSE(formatoValido(a, canal, profundidad));
}

TEST(formatoValidoTEST,audioValidoConCasosBordes){
    audio a = {-16,15,3,2,-14,-16,15,15,-16};
    int canal = 3;
    int profundidad = 5;

    EXPECT_TRUE(formatoValido(a, canal, profundidad));
}
