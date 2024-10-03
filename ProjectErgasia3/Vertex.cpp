#include <iostream>
#include <vector>


#include "ImageVector.h"
#include "Edge.h"
#include "Vertex.h"
#include "Neighbour.h"

using namespace std;

void Vertex::addNeighbour(Vertex* v, double distance){

    Edge* edge = new Edge(v,distance);

    //Insert allocated edge to Vertex 
    NeighbourVertices.push_back(edge);
    
}

vector<Edge*> Vertex::getNeighbours(int E){

    
   std::vector<Edge*> neighbours;

    int counter = 0;
    for (Edge* edge : this->NeighbourVertices) {
        if (counter == E) {
            break;
        }
        neighbours.push_back(edge);
        counter++;
    }

    return neighbours;

}


void Vertex::displayVertex(){

    
    
    for (const auto& edge : this->NeighbourVertices) {
       cout << " (Dest: " << edge->destination->vertex->id << ", Dist: " << edge->distance << ")";
    }
    cout << endl;

}

void Vertex::displayVertexMRNG(){

    
    
    for (const auto& edge : this->MRNGNeighbourVertices) {
       cout << " (Dest: " << edge->destination->vertex->id << ", Dist: " << edge->distance << ")";
    }
    cout << endl;

}

Vertex::~Vertex(){

    for (Edge* edge : this->NeighbourVertices) {
        delete edge;
    }

   this->NeighbourVertices.clear();


}