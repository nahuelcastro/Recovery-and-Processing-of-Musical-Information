#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(magnitudAbsolutaMaximaTEST, unCanal){
    audio a = {1,2,3,-2};
    int canal = 1;
    int profundidad = 6;
    audio maximos, posicionesMaximos = {};

    audio maximosEsperados = {3};
    audio posicionesMaximosEsperados = {2};

    magnitudAbsolutaMaxima(a, canal, profundidad, maximos, posicionesMaximos);

    ASSERT_VECTOR(maximos, maximosEsperados);
    ASSERT_VECTOR(posicionesMaximos, posicionesMaximosEsperados);
}
TEST(magnitudAbsolutaMaximaTEST, tresCanales){
    audio a = {1,2,3,6,2,6,9,0,12,8,31,17};
    int canal = 3;
    int profundidad = 6;
    audio maximos, posicionesMaximos = {};

    audio maximosEsperados = {9,31,17};
    audio posicionesMaximosEsperados = {6,10,11};

    magnitudAbsolutaMaxima(a, canal, profundidad, maximos, posicionesMaximos);

    ASSERT_EQ(maximos, maximosEsperados);
    ASSERT_EQ(posicionesMaximos, posicionesMaximosEsperados);
}
TEST(magnitudAbsolutaMaximaTEST, seisCanalesYTomaLasEntradasPorReferenciaConBasura){
    audio a = {1,2,3,96,2,6,9,0,12,8,31,17};
    int canal = 6;
    int profundidad = 6;
    audio maximos {3,5,1111,454,64,24,68,89,865,43};
    audio posicionesMaximos = {0,9,88,6,4,4553,333,55,3,14,6,73,2,23,13,24};

    audio maximosEsperados = {9,2,12,96,31,17};
    audio posicionesMaximosEsperados = {6,1,8,3,10,11};

    magnitudAbsolutaMaxima(a, canal, profundidad, maximos, posicionesMaximos);

    ASSERT_EQ(maximos, maximosEsperados);
    ASSERT_EQ(posicionesMaximos, posicionesMaximosEsperados);
}

// falta hacer ahora que me entere que va con modulo

TEST(magnitudAbsolutaMaximaTEST, tresCanalesConAlgunMaximoNegativo){
    audio a = {1,2,3,6,2,6,-20,0,12,8,31,-30};
    int canal = 3;
    int profundidad = 6;
    audio maximos, posicionesMaximos = {};

    audio maximosEsperados = {-20,31,-30};
    audio posicionesMaximosEsperados = {6,10,11};

    magnitudAbsolutaMaxima(a, canal, profundidad, maximos, posicionesMaximos);

    ASSERT_EQ(maximos, maximosEsperados);
    ASSERT_EQ(posicionesMaximos, posicionesMaximosEsperados);
}
TEST(magnitudAbsolutaMaximaTEST, tresCanalesConAlunMaximoNegativo){
    audio a = {14,-20,2,-20,2,-20,14,-20};
    int canal = 2;
    int profundidad = 6;
    audio maximos, posicionesMaximos = {3,4,2,4};

    audio maximosEsperados = {14,-20};
    audio posicionesMaximosEsperados = {6,7};

    magnitudAbsolutaMaxima(a, canal, profundidad, maximos, posicionesMaximos);

    ASSERT_EQ(maximos, maximosEsperados);
    ASSERT_EQ(posicionesMaximos, posicionesMaximosEsperados);
}