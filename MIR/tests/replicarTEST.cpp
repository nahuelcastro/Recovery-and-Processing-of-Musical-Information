#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(replicarTEST, unCanal){
    audio a = {1,2,3,-5,-2,-10,0};
    int canal = 1;
    int profundidad = 6;
    audio esperado = {1,2,3,-5,-2,-10,0};

    ASSERT_VECTOR(replicar(a, canal, profundidad), esperado);
}
TEST(replicarTEST, tresCanales){
    audio a = {1,2,3,-5,-2,-10,0};
    int canal = 3;
    int profundidad = 6;
    audio esperado = {1,2,3,-5,-2,-10,0,1,2,3,-5,-2,-10,0,1,2,3,-5,-2,-10,0};

    ASSERT_EQ(replicar(a, canal, profundidad), esperado);
}
TEST(replicarTEST, 4Canales){
    audio a = {1,31,-30,0,-27};
    int canal = 4;
    int profundidad = 6;
    audio esperado = {1,31,-30,0,-27,1,31,-30,0,-27,1,31,-30,0,-27,1,31,-30,0,-27};

    ASSERT_EQ(replicar(a, canal, profundidad), esperado);
}