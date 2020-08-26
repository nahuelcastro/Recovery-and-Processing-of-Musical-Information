#include <algorithm>
#include <gtest/gtest.h>
#include "solucion.h"
#include "auxiliares.h"
#include <iostream>
#include <fstream>


bool vectoresOrdenadosIguales(vector<int> vector1, vector<int> vector2){
    if(vector1.size() != vector2.size())
        return false;

    for (int i = 0; i < vector1.size(); ++i)
        if (vector1[i] != vector2[i]){return false;}

    return true;
}

bool todasSusFilasEnLaOtraMatriz(vector<vector<int> > mat1, vector<vector<int> > mat2) {
    bool res;
    
    for (int i = 0; i < mat1.size(); ++i){
        res = false;
        for (int j = 0; j < mat2.size(); ++j) {
            if (vectoresOrdenadosIguales(mat1[i], mat2[j])) {
                res = true;
                break;
            }
        }
        if(!res)
            return false;
    }

    return true;
}

bool matricesIguales(vector<vector<int> > mat1, vector<vector<int> > mat2){
    if(mat1.size() != mat2.size())
        return false;

    for (int i = 0; i < mat1.size(); ++i) {
        sort(mat1[i].begin(), mat1[i].end());
        sort(mat2[i].begin(), mat2[i].end());
    }

    return todasSusFilasEnLaOtraMatriz(mat1,mat2) && todasSusFilasEnLaOtraMatriz(mat2,mat1);
}

void ASSERT_VECTOR(vector<int> vector1, vector<int> vector2) {
    sort(vector1.begin(), vector1.end());
    sort(vector2.begin(), vector2.end());

    ASSERT_TRUE(vectoresOrdenadosIguales(vector1, vector2));
}

void ASSERT_MATRIX(vector<audio> mat1, vector<audio> mat2) {
    ASSERT_TRUE(matricesIguales(mat1, mat2));
}


void mostrar_vector(vector<int>& v){
    string vector = "{";
    if(v.size() > 0){
        for(int i=0; i < v.size()-1; i++){
            vector = vector + to_string(v[i]) + ",";
        }
    }

    if(v.size() != 0){
        vector = vector + to_string(v[v.size()-1]) + "]";
    }else{
        vector = vector + "}";
    }

    cout << vector << endl;
}

vector<int> construir_vector(int n, string disposicion){

    vector<int> res;
    srand (time(NULL));
    int numero;

    if (disposicion == "asc"){
        for(int i=0; i < n; i++){
            res.push_back(i);
        }
    }else if(disposicion == "desc"){
        for(int i=n-1; i >= 0; i--){
            res.push_back(i);
        }

    }else if(disposicion == "azar"){
        for(int i=0; i < n; i++){
            numero = rand() % (30 - (-30)) -30;
            res.push_back(numero);
        }
    }else if(disposicion == "iguales"){
        numero = rand() % 100;
        for(int i=0; i < n; i++){
            res.push_back(numero);
        }
    }else{
        cout << "Dispocisión no válida" << endl;
    }

    return res;
}




// /////////////////////////////////////////////////////////////////////////////


bool esSoft(audio &a, int &umbral, int &longitud){
    if (a.size()<longitud){ // O(1)
        return true; // O(1)
    }
    int acum=0; //O 1)
    for (int i = 0; i < a.size() ; ++i) { // O(m) todo el for en el peor caso es m*K, siendo m la longitud del mayor audio dentro del vector de audios
        if(a[i]>umbral && acum == longitud){ // O(1)
            return false; // O(1)
        }
        if(a[i]>umbral){ // O(1)
            acum+=1; // O(1)
        }
        if(a[i]<umbral){ // O(1)
            acum=0; // O(1)
        }
    }
    return true; // O(1)
}


void calculateA1Positions(audio &a, audio &a1,int &acum, int &startPositionA1,int &endPositionA1){
    for (int i = 0; i < a.size() ; ++i) {
        if (a[i] == a1[acum]) {
            acum++;
            if (acum == 1) {
                startPositionA1 = i;
            }
            if (acum == a1.size()) {
                endPositionA1 = i;
                break;
            }
        } else {
            acum = 0;
            startPositionA1 = 0;
        }
    }
}

void concatV (vector<int>& a, vector<int>& b){
    for (int i = 0; i < b.size(); ++i) {
        a.push_back(b[i]);
    }
}

void copyAudioFragment(audio &a,int start,int end, audio &copy){
    for (int i = start; i <= end ; ++i) {
        copy.push_back(a[i]);
    }
}
void deleteAudioFragment(audio &a, int end){
    for (int i = a.size()-1; i > end ; --i) {
        a.pop_back();
    }
}

void selectionSort (audio &a){
    for (int j = 0; j < a.size() ; ++j) {
        int minimunPosition = getMinimumPositionFrom(a,j);
        int swapAux = a[j];
        a[j]=a[minimunPosition];
        a[minimunPosition]=swapAux;
    }
}

int getMinimumPositionFrom (audio &a,int &from){
    int minimumPositionCandidate=from;
    for (int i = from; i < a.size() ; ++i) {
        if(a[i]<a[minimumPositionCandidate]){
            minimumPositionCandidate=i;
        }
    }
    return minimumPositionCandidate;
}

int getPercentil95 (audio &a){
    int percentil=0;
    percentil= a[int(0.95*a.size())];
    return percentil;
}

void setOutliersPositions (audio &a,vector<int> &outliers, int percentil){
    outliers={};
    for (int i = 0; i < a.size(); ++i) {                       //O(n)
        if(isOutlier(a[i],percentil)){                  //O(1)
            outliers.push_back(i);                             //O(1)
        }
    }
}

bool isOutlier (int &n,int &percentil){                        // O(1)
    return n>percentil;
}

tuple<bool,int> noOutlierRight(audio &a,int &outlierPosition,int &percentil){ // O(n^2)
    for (int i = outlierPosition + 1 ; i < a.size() ; ++i) {
        if (!isOutlier(a[i],percentil)){
            return make_tuple(true,i);
        }
    }
    return make_tuple(false,0);
}

tuple<bool,int> noOutlierLeft(audio &a,int &outlierPosition,int &percentil){
    for (int i = outlierPosition - 1 ; i >= 0 ; --i) {
        if (!isOutlier(a[i],percentil)){
            return make_tuple(true,i);
        }
    }
    return make_tuple(false,0);
}

void modifyOnlyOutliers (audio &a, vector<int> &outliers, int &percentil){
    for (int i = 0; i < a.size() ; ++i) {
        if(isOutlier(a[i],percentil)){
            modifyOutlier(a,outliers,percentil,i);
        }
    }
}

void modifyOutlier(audio &a, vector<int> &outliers, int &percentil,int &i){
    tuple<bool,int> noOutlierRightInfo = noOutlierRight(a,i,percentil);
    tuple<bool,int> noOutlierLeftInfo = noOutlierLeft(a,i,percentil);

    bool haveOutlierRight = get<0>(noOutlierRightInfo);
    bool haveOutlierLeft = get<0>(noOutlierLeftInfo);
    int positionOfFirstNoOutlierRight= get<1>(noOutlierRightInfo);
    int positionOfFirstNoOutlierLeft= get<1>(noOutlierLeftInfo);

    if(haveOutlierRight && haveOutlierLeft){
        int sumOfBoth = a[positionOfFirstNoOutlierRight] + a[positionOfFirstNoOutlierLeft];
        a[i]= floor((double)(sumOfBoth) / 2);
    } else if(haveOutlierRight){
        a[i]= a[positionOfFirstNoOutlierRight];
    } else if(haveOutlierLeft){
        a[i]= a[positionOfFirstNoOutlierLeft];
    }
}




// ////////////////////// COMPLEJIDAD


void guardarTiempos (string name){
    int hasta = 25000; int paso = 1000; int p = 21; int c = 2;
    if(name=="revertirAudio"){
        ofstream fout;
        fout.open("datosrevertirAudio.csv");
        fout << "n\t" << "tiempo" <<endl;
        for (int n = 0; n < hasta ; n += paso) {
            vector<int> a = construir_vector(n, "azar");
            hasta=30000;
            paso=1000;
            double t0 = clock();
            revertirAudio(a,c,p);
            double t1 = clock();
            double tiempo = (double(t1-t0)/CLOCKS_PER_SEC);
            fout << n << "\t" << tiempo << endl;
        }
        fout.close();
    }else if (name=="limpiarAudio"){
        ofstream fout2;
        fout2.open("datoslimpiarAudio.csv");
        fout2 << "n\t" << "tiempo" <<endl;
        for (int n = 1000; n < hasta + 1000 ; n += paso) {
            p=27;
            vector<int> outliers;
            vector<int> a = construir_vector(n, "asc");
            double t0 = clock();
            limpiarAudio(a,p,outliers);
            double t1 = clock();
            double tiempo = (double(t1-t0)/CLOCKS_PER_SEC);
            fout2 << n << "\t" << tiempo << endl;
        }
        fout2.close();
    }else if (name=="maximosTemporales"){
        ofstream fout3;
        fout3.open("datosMáximosTemporales.csv");
        fout3 << "n\t" << "tiempo" <<endl;
        vector <pair<int,int> > intervalos = {{1,2},{2,2}};
        vector<int> tiempos = {p,p*2};
        vector <int> maximos = {1};
        for (int n = 1000; n < hasta + 1000 ; n += paso) {
            vector<int> a = construir_vector(n, "asc");
            double t0 = clock();
            maximosTemporales(a, 1, tiempos, maximos, intervalos);
            double t1 = clock();
            double tiempo = (double(t1-t0)/CLOCKS_PER_SEC);
            fout3 << n << "\t" << tiempo << endl;
        }
        fout3.close();
    }
}



