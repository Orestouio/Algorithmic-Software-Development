#ifndef CubeFunctions_Headers
#define CubeFunctions_Headers

#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
#include <list>


#include "ImageVector.h"


using namespace std;

extern int magic_number, num_images, num_rows, num_cols;
extern int magic_numberQ, num_imagesQ, num_rowsQ, num_colsQ;


double calculateEuclideanDistance(ImageVector*, ImageVector*);
double calculateHammingDistance(string, string);
vector<ImageVector> readImages(const string&);
vector<ImageVector> readQuery(const string& filename);

#endif
