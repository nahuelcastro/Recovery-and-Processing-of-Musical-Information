#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(redirigirTEST, audioTodosCeros){
    audio a = {0,0,0,0,0,0};
    int canal = 1;
    int profundidad = 6;
    audio esperado = {0,0,0,0,0,0};

    ASSERT_VECTOR(redirigir(a, canal, profundidad), esperado);
}

TEST(redirigirTEST, canalFueraDeRango){
    audio a = {1,2,3,-5,-2,-10};
    int canal = 10;
    int profundidad = 6;
    audio esperado = {1,2,3,-5,-2,-10};

    ASSERT_VECTOR(redirigir(a, canal, profundidad), esperado);
}

TEST(redirigirTEST, canalDosTodosEnProfundidadCorrecta){
    audio a = {1,2,0,-5,-2,10,-5,-5,10,32};
    int canal = 2;
    int profundidad = 6;
    audio esperado = {1,2,-5,-5,12,10,0,-5,22,32};

    ASSERT_VECTOR(redirigir(a, canal, profundidad), esperado);
}

TEST(redirigirTEST, canalDosNoTodosEnProfundidadCorrecta){
    audio a = {1,29,-56,12,32,-33,-1,0,52,-20};
    int canal = 2;
    int profundidad = 2;
    audio esperado = {2,29,2,12,-2,-33,1,0,-2,-20};

    ASSERT_VECTOR(redirigir(a, canal, profundidad), esperado);
}

TEST(redirigirTEST, canalUnoTodosEnProfundidadCorrecta){
    audio a = {1,2,0,-5,-2,10,-3,-3,10,32};
    int canal = 1;
    int profundidad = 7;
    audio esperado = {1,1,0,-5,-2,12,-3,0,10,22};

    ASSERT_VECTOR(redirigir(a, canal, profundidad), esperado);
}

TEST(redirigirTEST, canalUnoNoTodosEnProfundidadCorrecta){
    audio a = {1,29,-56,12,32,-33,-1,0,52,-20};
    int canal = 1;
    int profundidad = 3;
    audio esperado = {1,4,-56,4,32,-4,-1,1,52,-4};

    ASSERT_VECTOR(redirigir(a, canal, profundidad), esperado);
}