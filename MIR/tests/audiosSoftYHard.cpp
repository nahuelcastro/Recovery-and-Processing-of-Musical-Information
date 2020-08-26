#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(audiosSoftYHardTEST, listaVacia){
    vector<audio> as = {};
    int profundidad = 8;
    int longitud = 2;
    int umbral = 2;
    vector<audio> soft = {};
    vector<audio> hard = {};

    vector<audio> esperadoSoft = {};
    vector<audio> esperadoHard = {};

    audiosSoftYHard(as, profundidad, longitud, umbral, soft, hard);

    ASSERT_MATRIX(soft, esperadoSoft);
    ASSERT_MATRIX(hard, esperadoHard);
}


TEST(audiosSoftYHardTEST, listaEnterosUmbralPositivoTodosSoft){
    vector<audio> as = {{120,1,2,34,56,76,45,3}, {10,122,-354,-12,150,-150,0}};
    int profundidad = 8;
    int longitud = 2;
    int umbral = 148;
    vector<audio> soft = {{123,123,-123,12,3}};
    vector<audio> hard = {{12,232,32,-2}};

    vector<audio> esperadoSoft = {{120,1,2,34,56,76,45,3},{10,122,-354,-12,150,-150,0}};
    vector<audio> esperadoHard = {};

    audiosSoftYHard(as, profundidad, longitud, umbral, soft, hard);

    ASSERT_MATRIX(soft, esperadoSoft);
    ASSERT_MATRIX(hard, esperadoHard);
}


TEST(audiosSoftYHardTEST, listaEnterosUmbralPositivoSoftYHard){
    vector<audio> as = {{120,1,2,84,56,76,45,3}, {10,122,-354,-12,150,-150,0}};
    int profundidad = 8;
    int longitud = 2;
    int umbral = 55;
    vector<audio> soft = {{123,123,-123,12,3}};
    vector<audio> hard = {{12,232,32,-2}};

    vector<audio> esperadoSoft = {{10,122,-354,-12,150,-150,0}};
    vector<audio> esperadoHard = {{120,1,2,84,56,76,45,3}};

    audiosSoftYHard(as, profundidad, longitud, umbral, soft, hard);

    ASSERT_MATRIX(soft, esperadoSoft);
    ASSERT_MATRIX(hard, esperadoHard);
}

TEST(audiosSoftYHardTEST, listaEnterosUmbralPositivoTodosHard){
    vector<audio> as = {{120,1,2,3,56,76,45,5}, {10,122,354,12,-10,150,-150,0}};
    int profundidad = 8;
    int longitud = 3;
    int umbral = 4;
    vector<audio> soft = {{123,123,-123,12,3}};
    vector<audio> hard = {{12,232,32,-2}};

    vector<audio> esperadoSoft = {};
    vector<audio> esperadoHard = {{120,1,2,3,56,76,45,5}, {10,122,354,12,-10,150,-150,0}};

    audiosSoftYHard(as, profundidad, longitud, umbral, soft, hard);

    ASSERT_MATRIX(soft, esperadoSoft);
    ASSERT_MATRIX(hard, esperadoHard);
}

TEST(audiosSoftYHardTEST, listaEnterosUmbralNegativoSoftYHard){
    vector<audio> as = {{120,-46,2,-84,56,-76,-45,3}, {-10,-122,-354,-12,150,-150,0}};
    int profundidad = 10;
    int longitud = 1;
    int umbral = -45;
    vector<audio> soft = {{123,123,-123,12,3}};
    vector<audio> hard = {{12,232,32,-2}};

    vector<audio> esperadoSoft = {{120,-46,2,-84,56,-76,-45,3}};
    vector<audio> esperadoHard = {{-10,-122,-354,-12,150,-150,0}};

    audiosSoftYHard(as, profundidad, longitud, umbral, soft, hard);

    ASSERT_MATRIX(soft, esperadoSoft);
    ASSERT_MATRIX(hard, esperadoHard);
}

TEST(audiosSoftYHardTEST, algunAudioTieneSizeMenorALongitud){
    vector<audio> as = {{4,79,-50,100}, {10,21,30,40,26,70,90}};
    int profundidad = 10;
    int longitud = 5;
    int umbral = 20;
    vector<audio> soft = {{4,755,343}};
    vector<audio> hard = {{10,99,70,90}};

    vector<audio> esperadoSoft ={{4,79,-50,100}};
    vector<audio> esperadoHard = {{10,21,30,40,26,70,90}};

    audiosSoftYHard(as, profundidad, longitud, umbral, soft, hard);

    ASSERT_MATRIX(soft, esperadoSoft);
    ASSERT_MATRIX(hard, esperadoHard);
}