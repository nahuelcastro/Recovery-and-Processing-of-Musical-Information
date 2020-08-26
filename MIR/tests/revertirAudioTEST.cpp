#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(revertirAudioValidoTEST, unCanal){
    audio a = {1,2,3,-5,-2,-10,0};
    int canal = 1;
    int profundidad = 6;
    audio esperado = {0,-10,-2,-5,3,2,1};

    ASSERT_VECTOR(revertirAudio(a, canal, profundidad), esperado);
}
TEST(revertirAudioValidoTEST, tresCanales){
    audio a = {2,31,-5,-32,-10,0,1,2,3};
    int canal = 3;
    int profundidad = 6;
    audio esperado = {1,2,3,-32,-10,0,2,31,-5};

    ASSERT_EQ(revertirAudio(a, canal, profundidad), esperado);
}
TEST(revertirAudioValidoTEST, seisCanales){
    audio a = {2,31,-5,-32,-10,0,1,2,3,9,24,12,-13,15,-6,3,1,30};
    int canal = 6;
    int profundidad = 7;
    audio esperado = {-13,15,-6,3,1,30,1,2,3,9,24,12,2,31,-5,-32,-10,0};

    ASSERT_EQ(revertirAudio(a, canal, profundidad), esperado);
}