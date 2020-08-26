#ifndef RECUPERACIONINFORMACIONMUSICAL_AUXILIARES_H
#define RECUPERACIONINFORMACIONMUSICAL_AUXILIARES_H

#include "definiciones.h"

//template<typename T>
bool vectoresOrdenadosIguales(vector<int> vector1, vector<int> vector2);
//template<typename T>
void mostrar_vector(vector<int>& v);
vector<int> construir_vector(int n, string disposicion);
void ASSERT_VECTOR(vector<int> vector1, vector<int> vector2);
void ASSERT_MATRIX(vector<audio> mat1, vector<audio> mat2);
//          ////////////////////////////////////                 //
void calculateA1Positions(audio &a, audio &a1,int &acum, int &startPositionA1,int &endPositionA1);
void concatV (vector<int>& a, vector<int>& b);
void copyAudioFragment(audio &a, int start,int end, audio &copy);
void deleteAudioFragment(audio &a, int end);
bool isOutlier (int &n,int &percentil);
void setOutliersPositions (audio &a,vector<int> &outliers, int percentil);
void selectionSort (audio &a);
int getMinimumPositionFrom (audio &a,int &from);
int getPercentil95 (audio &a);
tuple<bool,int> noOutlierRight(audio &a,int &outlierPosition,int &percentil);
tuple<bool,int> noOutlierLeft(audio &a,int &outlierPosition,int &percentil);
bool esSoft(audio &a, int &umbral, int &longitud);
void guardarTiempos (string name);
void modifyOnlyOutliers (audio &a, vector<int> &outliers, int &percentil);
void modifyOutlier(audio &a, vector<int> &outliers, int &percentil,int &i);



#endif //RECUPERACIONINFORMACIONMUSICAL_AUXILIARES_H
