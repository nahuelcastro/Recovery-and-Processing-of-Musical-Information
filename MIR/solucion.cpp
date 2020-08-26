#include "solucion.h"
#include "auxiliares.h"
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

bool formatoValido(audio a, int canal, int profundidad) {
    bool validSizeAndMod = false;
    bool allInDepth = true; // todos en profundidad
    int auxP = profundidad-1;
    if (a.size()>0 && a.size() % canal ==0){
        validSizeAndMod = true;
    }
    for (int i = 0; i < a.size() ; ++i) {
        if( a[i] < (-1)*pow(2,auxP)  || a[i] > pow(2,auxP) -1 ){
            allInDepth= false;
            break;
        }
    }
    return validSizeAndMod && allInDepth;
}

audio replicar(audio a, int canal, int profundidad) {
    audio a0 = a;
    for (int c = 1; c < canal ; ++c) {
        concatV(a,a0);
    }
    return a;
}

audio revertirAudio(audio a, int canal, int profundidad) {
    audio res = a;                                                   // O(n)
    for (int block = 0; block < a.size()/canal ; ++block) {          // O((n/c)*c) =  O(n)
        for (int j = 0; j < canal ; ++j) {                              // O(n/c)
            res[canal*block + j] = a[a.size() - canal*(block+1) + j];   // O(1)
        }
    }
    return res;
}


void magnitudAbsolutaMaxima(audio a, int canal, int profundidad, vector<int> &maximos, vector<int> &posicionesMaximos) {
    maximos={};
    posicionesMaximos={};
    for (int c = 0; c < canal; ++c) { // itero por los canales
        int maxCandidate = a[c];
        int posCandidate = c;
        for (int i = 0; i < a.size()/canal ; ++i) {
            if (abs(a[c + canal*i]) >= abs(maxCandidate)){
                maxCandidate=a[c+canal*i];
                posCandidate= c+canal*i;
            }
        }
        maximos.push_back(maxCandidate);
        posicionesMaximos.push_back(posCandidate);
    }
}

audio redirigir(audio a, int canal, int profundidad) {
    for (int i = 0; i < a.size(); i++) {
        if(canal==2 && i%2 == 0){
            if(a[i+1]-a[i]<(pow(-2,profundidad-1))){
                a[i]=pow(-2,profundidad-1);
            }
            else if(a[i+1]-a[i]>=(pow(2,profundidad-1))){
                a[i]=pow(2,profundidad-1);
            }
            else{
                a[i]=a[i+1]-a[i];
            }
        }
        if(canal==1 && i%2 == 1){
            if((a[i]-a[i-1])<(-1)*(pow(2,profundidad-1))){
                a[i]=pow(2,profundidad-1)*(-1);
            }
            else if(a[i]-a[i-1]>=(pow(2,profundidad-1))){
                a[i]=pow(2,profundidad-1);
            }
            else{
                a[i]=a[i]-a[i-1];
            }
        }
    }
    return a;
}

void bajarCalidad(vector<audio> & as, int profundidad1, int profundidad2) {
    for (int i = 0; i < as.size() ; ++i) {
        for (int j = 0; j < as[i].size() ; ++j) {
            as[i][j]= floor((double)(as[i][j]) / pow(2,profundidad1-profundidad2));
        }
    }
}

void audiosSoftYHard(vector<audio> as, int profundidad, int longitud, int umbral, vector<audio>& soft, vector<audio>& hard) {
    soft={};
    hard={};
    for (int i = 0; i < as.size() ; ++i) {
        if (esSoft(as[i], umbral, longitud)) {
            soft.push_back(as[i]);
        } else if (!esSoft(as[i], umbral, longitud)) {
            hard.push_back(as[i]);
        }
    }
}



void reemplazarSubAudio(audio& a, audio a1, audio a2, int profundidad) {
    int acum = 0;
    int endPositionA1=0;
    int startPositionA1=0;
    calculateA1Positions(a,a1,acum,startPositionA1,endPositionA1);
    if (acum!=0){
        audio finalAudioFragment={};
        copyAudioFragment(a,endPositionA1+1,a.size()-1,finalAudioFragment);
        deleteAudioFragment(a,startPositionA1-1);
        concatV(a,a2);
        concatV(a,finalAudioFragment);
    }
}

void maximosTemporales(audio a, int profundidad, vector<int> tiempos, vector<int>& maximos, vector<pair<int,int> >& intervalos) {
    maximos ={}; //O(1)
    intervalos = {}; //O(1)
    int maxNum = 0; //O(1)
    int ultimo=0; //O(1)
    for (int i = 0; i < tiempos.size() ; ++i) { //O(m)
        for (int j = 0; j < a.size(); ++j) { //O(n)
            if(abs(a[j])>abs(maxNum)){ //O(1)
                maxNum=a[j]; //O(1)
            }
            if((j+1)%tiempos[i]==0){ //O(1)
                maximos.push_back(maxNum); //O(1)
                maxNum=0; //O(1)
                intervalos.push_back(make_pair(j+1-tiempos[i],j)); //O(1)
                ultimo=j; //O(1)
            }else if(j+1==a.size() && (j+1)%tiempos[i]!=0){ //O(1)
                maximos.push_back(maxNum); //O(1)
                maxNum=0; //O(1)
                intervalos.push_back(make_pair((ultimo+1),ultimo+tiempos[i])); //O(1)
            }
        }
    }
}

void limpiarAudio(audio& a, int profundidad, vector<int>& outliers) {
    audio a0Sort=a;
   selectionSort(a0Sort);
   int percentil= getPercentil95(a0Sort);
    setOutliersPositions(a,outliers,percentil);
    modifyOnlyOutliers(a,outliers,percentil);
}

void escribirAudio(audio a, string nombreArchivo, int c){
    ofstream fout;
    fout.open(nombreArchivo);
    fout << c << " ";
    for (int i = 0; i < a.size() ; ++i) {
        fout << a[i] << " ";
    }
    fout << endl;
    fout.close();
}

tuple<int, audio> leerAudio (string nombreArchivo) {
    ifstream fin;
    fin.open(nombreArchivo);
    int resultCanal = 0;
    audio resultAudio;
    fin >> resultCanal;
    int elemAudio = 0;
    while (!fin.eof()) {
        fin >> elemAudio;
        resultAudio.push_back(elemAudio);
    }
    tuple<int, vector<int>> resultTuple = make_tuple(resultCanal, resultAudio);
    return resultTuple;
}