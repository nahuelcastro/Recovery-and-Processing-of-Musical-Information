#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"


TEST(escribirAudioTEST, audioCompleto){
    audio a = {3,4,1,2,5,7,6,4,5,3,6,7,9,-8};
    string nameFile="writtenAudioTest.txt";
    int c = 2;
    escribirAudio(a,nameFile,c);
    ASSERT_EQ(leerAudio("writtenAudioTest.txt"), leerAudio("expectedAudioTest.txt")); // aca estamos suponiendo que leerAudio funciona exactamente como queremos, ya que sus test los hicimos y pasaron
}
