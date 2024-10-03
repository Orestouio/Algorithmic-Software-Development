#ifndef Vertex_Headers
#define Vertex_Headers


#include <iostream>
#include <vector>

#include "ImageVector.h"
#include "Edge.h"
#include "MRNGEdge.h"

using namespace std;

class Edge;

class MRNGEdge;

class Vertex{

    public:

    //Datapoint
    ImageVector* vertex;

    //Vector of pointers to neighbour vertices
    vector<Edge*> NeighbourVertices;

    //Vector of pointers to neighbour vertices after MRNGindex
    vector<Edge*> MRNGNeighbourVertices;


    //Constructor
    Vertex(ImageVector* image) : vertex(image) {}

    //Add Edge
    void addNeighbour(Vertex*, double);

    //Get Neighbours
    vector<Edge*> getNeighbours(int);
    
    //Display info about vertex
    void displayVertex();

    void displayVertexMRNG();

    ~Vertex();

};

#endif