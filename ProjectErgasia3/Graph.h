#ifndef Graph_Headers
#define Graph_Headers

#include <iostream>
#include <list>
#include <vector>

#include "ImageVector.h"
#include "Vertex.h"
#include "Edge.h"
#include "MRNGEdge.h"

using namespace std;

class Graph
{

private:
    // Number of vertices
    int numberOfVertices;

    // Vertices in Graph
    vector<Vertex *> vertices;

    // Navigation Node
    int NavNode;

public:
    // Initialize
    void initializeGraph();

    // Add vertex (new vertices)
    Vertex *addVertex(ImageVector *);

    // Add Vertex Neighbour (Takes 2 vertices and connects them)
    void addVertexNeighbour(ImageVector *, ImageVector *);

    // Graph Nearest Neighbour Search
    vector<Neighbour *> GNN(ImageVector *, int, int, int, int);

    // Construction of index
    vector<MRNGEdge *> constructIndex();

    // Connect vertices with MRNG edges
    void connectMRNGEdges(vector<MRNGEdge *>);

    // Search on Graph for knn
    vector<Neighbour *> searchOnGraph(ImageVector *, int k);

    int getNavNode();

    // Get vertices
    vector<Vertex *> getVertices();

    // Set NavNode
    void setNavNode(int);

    // Print Graph
    void printGraph();

    // Print MRNG Graph
    void printGraphMRNG();

    void compareResults(const vector<ImageVector> &,
                        const vector<ImageVector> &,
                        const vector<vector<Neighbour>> &);

    ~Graph();
    bool vertexExists(ImageVector *);
    double getNeighborDistance(ImageVector *, ImageVector *);
};

ImageVector findImageById(const vector<ImageVector> &, int);

#endif