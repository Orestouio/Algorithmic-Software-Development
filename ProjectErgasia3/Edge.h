#ifndef Edge_Headers
#define Edge_Headers


#include <iostream>
#include <vector>

#include "ImageVector.h"
#include "Vertex.h"

using namespace std;

class Vertex;

class Edge{

public:

    //Destination vertex 
    Vertex* destination;

    //L2 distance to destination vertex (edge cost)
    double distance;

    //Constructor
    Edge(Vertex* dest, double dist) : destination(dest), distance(dist) {}


};

#endif