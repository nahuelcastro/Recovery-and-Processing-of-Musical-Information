#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(maximosTemporalesTEST, audioPositivosCompletoDosTiempos){
    audio a ={1,2,3,4,5,6};
    vector<int> tiempos = {2,3};
    vector <int> maximos;
    int profundidad = 1;
    vector<pair<int,int> > intervalos;
    maximosTemporales(a, profundidad, tiempos, maximos, intervalos);
    vector<int> maximoEsperado={2,4,6,3,6};
    vector<pair<int,int> > intervaloEsperado={{0,1},{2,3},{4,5},{0,2},{3,5}};
    ASSERT_EQ(maximos, maximoEsperado);
    ASSERT_EQ(intervalos, intervaloEsperado);
}

TEST(maximosTemporalesTEST, audioEnterosCompletoDosTiempos){
    audio a ={0,-5,10,-2,1,-5,4,-20,15,2,12,0};
    vector<int> tiempos = {2,3};
    vector <int> maximos ={2,32341,41,235,253,12124,12,412,3412312,3};
    int profundidad = 2;
    vector<pair<int,int> > intervalos;
    maximosTemporales(a, profundidad, tiempos, maximos, intervalos);
    vector<int> maximoEsperado={-5,10,-5,-20,15,12,10,-5,-20,12};
    vector<pair<int,int> > intervaloEsperado={{0,1},{2,3},{4,5},{6,7},{8,9},{10,11},{0,2},{3,5},{6,8},{9,11}};
    ASSERT_EQ(maximos, maximoEsperado);
    ASSERT_EQ(intervalos, intervaloEsperado);
}

TEST(maximosTemporalesTEST, audioCerosCompletoDosTiempos){
    audio a ={0,0,0,0,0,0,0,0,0,0,0,0};
    int profundidad = 1;
    vector<int> tiempos = {2,3};
    vector <int> maximos{12312,1231,3,123,13,23,123,23,123,123,123,12,312,312,312,31,23,12};
    vector<pair<int,int> > intervalos;
    maximosTemporales(a, profundidad, tiempos, maximos, intervalos);
    vector<int> maximoEsperado={0,0,0,0,0,0,0,0,0,0};
    vector<pair<int,int> > intervaloEsperado={{0,1},{2,3},{4,5},{6,7},{8,9},{10,11},{0,2},{3,5},{6,8},{9,11}};
    ASSERT_EQ(maximos, maximoEsperado);
    ASSERT_EQ(intervalos, intervaloEsperado);
}

TEST(maximosTemporalesTEST, audioTodosNegativosCompletoDosTiempos){
    audio a ={-2,-5,-10,-2,-1,-5,-4,-20,-15,-2,-12,-1};
    vector<int> tiempos = {2,3};
    int profundidad = 1;
    vector <int> maximos={213,12,312,312,312,3};
    vector<pair<int,int> > intervalos;
    maximosTemporales(a, profundidad, tiempos, maximos, intervalos);
    vector<int> maximoEsperado={-5,-10,-5,-20,-15,-12,-10,-5,-20,-12};
    vector<pair<int,int> > intervaloEsperado={{0,1},{2,3},{4,5},{6,7},{8,9},{10,11},{0,2},{3,5},{6,8},{9,11}};
    ASSERT_EQ(maximos, maximoEsperado);
    ASSERT_EQ(intervalos, intervaloEsperado);
}

TEST(maximosTemporalesTEST, audioEnterosIncompletoTresTiempos){
    audio a ={0,5,-10,-2,1,-7,5,10,-50,32,11};
    vector<int> tiempos = {2,3};
    vector <int> maximos={312,231,31,231,312,3};
    int profundidad = 1;
    vector<pair<int,int> > intervalos={{23,13},{3,3},{3,3}};
    maximosTemporales(a, profundidad, tiempos, maximos, intervalos);
    vector<int> maximoEsperado={5,-10,-7,10,-50,11,-10,-7,-50,32};
    vector<pair<int,int> > intervaloEsperado={{0,1},{2,3},{4,5},{6,7},{8,9},{10,11},{0,2},{3,5},{6,8},{9,11}};
    ASSERT_EQ(maximos, maximoEsperado);
    ASSERT_EQ(intervalos, intervaloEsperado);
}
