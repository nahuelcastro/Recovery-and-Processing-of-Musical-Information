#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

TEST(leerAudioTEST, leerAudio){
    tuple<int,vector<int>> readTuple = leerAudio("readAudioTest.txt");
    audio expectedAudio = {2,4,1,5,7,4,-10,-15,9,2,1,3,4,6,5};
    int expectedChannel = 3;
    tuple<int,vector<int>> expectedTuple = make_tuple(expectedChannel,expectedAudio);

    ASSERT_EQ(readTuple, expectedTuple);
}
TEST(leerAudioTEST, leerAudioVacio){
    tuple<int,vector<int>> readTuple = leerAudio("readCleanAudioTest.txt");
    audio expectedAudio = {};
    int expectedChannel = 1;
    tuple<int,vector<int>> expectedTuple = make_tuple(expectedChannel,expectedAudio);

    ASSERT_EQ(readTuple, expectedTuple);
}
TEST(leerAudioTEST, leerAudioConUnSoloElemento){
    tuple<int,vector<int>> readTuple = leerAudio("readOneElementAudioTest.txt");
    audio expectedAudio = {7};
    int expectedChannel = 1;
    tuple<int,vector<int>> expectedTuple = make_tuple(expectedChannel,expectedAudio);

    ASSERT_EQ(readTuple, expectedTuple);
}
