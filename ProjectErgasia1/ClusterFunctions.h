#ifndef ClusterFunctions_Headers
#define ClusterFunctions_Headers

#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
#include <list>


#include "ImageVector.h"


using namespace std;

extern int magic_number, num_images, num_rows, num_cols;
extern int magic_numberQ, num_imagesQ, num_rowsQ, num_colsQ;

vector<unsigned char> doublesToUnsignedChars(vector<double>&);
int binarySearch(double p[], int pSize, double x);
double calculateEuclideanDistance(ImageVector*, ImageVector*);
vector<ImageVector> readImages(const string&);
vector<ImageVector> readQuery(const string& filename);

#endif
