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
#include "Neighbour.h"

using namespace std;

class Vertex;
class Edge;

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

bool compareNeighbourDist(const Neighbour* a, const Neighbour* b);

struct NeighBrute{
    vector<Neighbour> Neigh;
};

//Find Nav Node
ImageVector* FindNavNode(vector<Vertex*>, ImageVector*);
//Calculate Graph Centroid
ImageVector* calculateCentroid(vector<ImageVector>&);
//Check if an edge is the lingest edge in triangle
bool isLongestEdgeInTriangle(Edge&, Edge& , Vertex*, Vertex* );
//Lp initialization function
vector<Edge*> initializeLp(vector<Edge*>, Vertex*);
//Check if vertex is in vector
bool isVertexInVector(Vertex*, const vector<Neighbour*>&);
//Find min element
Vertex* minElement(vector<Edge*>, ImageVector*);
int UniformDistributionGenerator(int);
int euclidean_mod(int, unsigned int);
//Make Graph using LSH
void LSHtoGraph(Graph* , int ,Hash_Table_LSH **,int, vector<ImageVector>&, int);
double calculateEuclideanDistance(ImageVector*, ImageVector*, int);
Hash_Table_LSH** CreateHashTables(int, int, int);
vector<ImageVector> readImages(const string&);
vector<ImageVector> readQuery(const string& filename);
vector<NeighbourBrute> FindNearestNeighborsBruteForce(ImageVector*, std::vector<ImageVector>&,double, int);
vector<NeighbourBrute> BruteForce(ImageVector *, std::vector<ImageVector>& , double , int);

#endif