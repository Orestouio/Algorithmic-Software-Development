#ifndef MRNGEdge_Headers
#define MRNGEdge_Headers

#include "ImageVector.h"
#include "Vertex.h"

using namespace std;

class Vertex;

class MRNGEdge{

public:

    //Source Vertex
    Vertex* source;

    //Destination vertex 
    Vertex* destination;

    //L2 distance to destination vertex (edge cost)
    double distance;

    //Constructor
    MRNGEdge(Vertex* src, Vertex* dest, double dist) : source(src), destination(dest), distance(dist) {}


};

#endif