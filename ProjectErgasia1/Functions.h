#ifndef Functions_Headers
#define Functions_Headers

#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
#include <list>
#include <algorithm>


#include "ImageVector.h"
#include "HashTableLSH.h"

using namespace std;

extern int magic_number, num_images, num_rows, num_cols;
extern int magic_numberQ, num_imagesQ, num_rowsQ, num_colsQ;

struct NeighbourBrute {
    int id;
    double distance;

    NeighbourBrute() : id(0), distance(0.0) {}  // Default constructor

    NeighbourBrute(int id, double distance) : id(id), distance(distance) {}

    // Overload the less than operator for NeighbourBrute
    bool operator<(const NeighbourBrute& other) const {
        return distance < other.distance;
    }
};

struct NeighBrute{
    vector<Neighbour> Neigh;
};

double calculateEuclideanDistance(ImageVector*, ImageVector*, int);
Hash_Table_LSH** CreateHashTables(int, int);
vector<ImageVector> readImages(const string&);
vector<ImageVector> readQuery(const string& filename);
vector<NeighbourBrute> FindNearestNeighborsBruteForce(ImageVector*, std::vector<ImageVector>&,double, int);
vector<NeighbourBrute> BruteForce(ImageVector *, std::vector<ImageVector>& , double , int);

#endif