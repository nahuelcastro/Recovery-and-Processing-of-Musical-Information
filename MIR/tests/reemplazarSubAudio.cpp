#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(reemplazarSubAudioTEST, unElementoYPresente){
    audio a = {1};
    audio a1 = {1};
    audio a2 = {3};
    int profundidad = 5;
    audio esperado = {3};

    reemplazarSubAudio(a, a1, a2, profundidad);

    ASSERT_VECTOR(a, esperado);
}
TEST(reemplazarSubAudioTEST, a1NoEstaContenido){
    audio a = {1,2,3,4,5,6};
    audio a1 = {3,4,6,5};
    audio a2 = {7,9,0,9,8};
    int profundidad = 5;
    audio esperado = {1,2,3,4,5,6};

    reemplazarSubAudio(a, a1, a2, profundidad);

    ASSERT_EQ(a, esperado);
}
TEST(reemplazarSubAudioTEST, variosElementosYA1Esta){
    audio a = {1,2,3,4,5,6};
    audio a1 = {3,4,5};
    audio a2 = {7,9,0,9,8};
    int profundidad = 5;
    audio esperado = {1,2,7,9,0,9,8,6};

    reemplazarSubAudio(a, a1, a2, profundidad);

    ASSERT_EQ(a, esperado);
}

TEST(reemplazarSubAudioTEST, a1PerteneceYTieneTieneLong1){
    audio a = {1,2,3,4,5,6};
    audio a1 = {3};
    audio a2 = {7,9,0,9,8};
    int profundidad = 5;
    audio esperado = {1,2,7,9,0,9,8,4,5,6};

    reemplazarSubAudio(a, a1, a2, profundidad);

    ASSERT_EQ(a, esperado);
}

TEST(reemplazarSubAudioTEST, a1Iguala){
    audio a = {1,2,3,4,5,6};
    audio a1 = {1,2,3,4,5,6};
    audio a2 = {9,0,9};
    int profundidad = 5;
    audio esperado = {9,0,9};

    reemplazarSubAudio(a, a1, a2, profundidad);

    ASSERT_EQ(a, esperado);
}