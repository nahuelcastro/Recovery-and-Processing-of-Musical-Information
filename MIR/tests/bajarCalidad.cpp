#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(bajarCalidadTEST, listaVacia){
    vector<audio> as = {};
    int profundidad1 = 4;
    int profundidad2 = 2;
    vector<audio> esperado = {};

    bajarCalidad(as, profundidad1, profundidad2);
    ASSERT_MATRIX(as, esperado);
}
TEST(bajarCalidadTEST, redondeoDePositivos){
    vector<audio> as = {{30,7,29}};
    int profundidad1 = 6;
    int profundidad2 = 4;
    vector<audio> esperado = {{7,1,7}};

    bajarCalidad(as, profundidad1, profundidad2);
    ASSERT_EQ(as, esperado);
}
TEST(bajarCalidadTEST, redondeoDeNegativos){
    vector<audio> as = {{-15,-32,-25}};
    int profundidad1 = 6;
    int profundidad2 = 4;
    vector<audio> esperado = {{-4,-8,-7}};

    bajarCalidad(as, profundidad1, profundidad2);
    ASSERT_EQ(as, esperado);
}
TEST(bajarCalidadTEST, unSoloAudio){
    vector<audio> as = {{30,7,-15,8,-32,0,29,-25}};
    int profundidad1 = 6;
    int profundidad2 = 4;
    vector<audio> esperado = {{7,1,-4,2,-8,0,7,-7}};

    bajarCalidad(as, profundidad1, profundidad2);
    ASSERT_EQ(as, esperado);
}
TEST(bajarCalidadTEST, variosAudios){
    vector<audio> as = {{30,7,-15,8,-32,0,29,-25},{-17,5,3},{30,7,-15,8,-32}};
    int profundidad1 = 6;
    int profundidad2 = 4;
    vector<audio> esperado = {{7,1,-4,2,-8,0,7,-7},{-5,1,0},{7,1,-4,2,-8}};

    bajarCalidad(as, profundidad1, profundidad2);
    ASSERT_EQ(as, esperado);
}
TEST(bajarCalidadTEST, variosAudiosConVaciosIncluidos){
    vector<audio> as = {{},{30,7,-15,8},{},{-17,5,3},{},{30,7,-15,8,-32},{}};
    int profundidad1 = 6;
    int profundidad2 = 4;
    vector<audio> esperado = {{},{7,1,-4,2},{},{-5,1,0},{},{7,1,-4,2,-8},{}};

    bajarCalidad(as, profundidad1, profundidad2);
    ASSERT_EQ(as, esperado);
}

