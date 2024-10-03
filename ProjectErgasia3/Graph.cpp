#include <iostream>
#include <vector>
#include <queue>

#include "ImageVector.h"
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Functions.h"
#include "MRNGEdge.h"

using namespace std;

class MRNGEdge;

// Check if vertex already exist
bool Graph::vertexExists(ImageVector *image)
{
    for (auto &vertex : this->vertices)
    {
        if (vertex->vertex->id == image->id)
        {
            return true; // Vertex found
        }
    }
    return false; // Vertex not found
}

double Graph::getNeighborDistance(ImageVector *image, ImageVector *neighborImage)
{
    for (auto &vertex : this->vertices)
    {
        if (vertex->vertex->id == image->id)
        {
            for (auto &edge : vertex->NeighbourVertices)
            {
                if (edge->destination->vertex->id == neighborImage->id)
                {
                    return edge->distance; // Return the distance if neighbor is found
                }
            }
            break; // No need to check other vertices
        }
    }
    return 0; // Return 0 if neighbor not found
}

void Graph::initializeGraph()
{
    numberOfVertices = 0;
}

Vertex *Graph::addVertex(ImageVector *image)
{

    Vertex *v = new Vertex(image);

    // Insert allocated vertex in Graph
    vertices.push_back(v);

    this->numberOfVertices++;

    return v;
}

void Graph::addVertexNeighbour(ImageVector *image, ImageVector *image2)
{

    for (const auto &vertex : this->vertices)
    {

        if (vertex->vertex->id == image->id)
        {

            double distance = calculateEuclideanDistance(image, image2, 2);

            // Search if destination vertex already exists
            for (const auto &Destvertex : this->vertices)
            {

                if (Destvertex->vertex->id == image2->id)
                {
                    vertex->addNeighbour(Destvertex, distance);
                    return;
                }
            }

            // If destination vertex does not exist create new and connect
            vertex->addNeighbour(addVertex(image2), distance);
            return;
        }
    }
    cout << "Input vertex " << image->id << " does not exist" << endl;
}

ImageVector findImageById(const vector<ImageVector> &dataset, int id)
{
    // Iterate through the originalData to find the image with the given id
    for (const auto &image : dataset)
    {
        if (image.id == id)
        {
            return image;
        }
    }
    // Handle case where the image is not found (can depend on how you want to manage this scenario)
}

vector<Neighbour *> Graph::GNN(ImageVector *Q, int R, int T, int E, int L)
{

    // Set S to store Neighbours
    vector<Neighbour *> S;

    Vertex *nextVertex = NULL;

    for (int r = 0; r < R; ++r)
    {
        Vertex *currentVertex = vertices[UniformDistributionGenerator(this->vertices.size())];

        for (int t = 0; t < T; ++t)
        {

            // Get current vertex neighbours
            vector<Edge *> currentVertexNeighbours = currentVertex->getNeighbours(E);

            // No more neighbours to explore
            if (currentVertexNeighbours.empty())
            {
                break;
            }

            // Find the min distance from query to vertex in neighbour list
            nextVertex = minElement(currentVertexNeighbours, Q);

            double currentDist = calculateEuclideanDistance(currentVertex->vertex, Q, 2);
            double nextDist = calculateEuclideanDistance(nextVertex->vertex, Q, 2);
            if (currentDist < nextDist)
            {
                break;
            }
            currentVertex = nextVertex;
        }

        // Add neighbour
        double dist = calculateEuclideanDistance(Q, currentVertex->vertex, 2);

        if (!isVertexInVector(currentVertex, S))
        {
            Neighbour *n = new Neighbour;
            n->distance = dist;
            n->id = currentVertex->vertex->id;

            // Push in set
            S.push_back(n);
        }
    }

    sort(S.begin(), S.end(), compareNeighbourDist);

    // //Debugging
    // cout<<"Printing Neighbours before returning"<<endl;
    // for (const auto& neigh : S) {
    //     cout << "Neighbour with id: "<< neigh->id<<" and distance "<< neigh->distance<<endl;

    // }

    // return vector with L objects
    return vector<Neighbour *>(S.begin(), S.begin() + min(L, static_cast<int>(S.size())));
}

vector<MRNGEdge *> Graph::constructIndex()
{

    vector<Vertex *> S = this->vertices;

    vector<Edge *> Rp;

    vector<MRNGEdge *> resultEdges;

    for (Vertex *p : S)
    {
        // Initialize Rp
        Rp = p->NeighbourVertices;

        // Sorting Rp
        sort(Rp.begin(), Rp.end(), [p](Edge *a, Edge *b)
             {
            double distanceA = calculateEuclideanDistance(a->destination->vertex, p->vertex, 2);
            double distanceB = calculateEuclideanDistance(b->destination->vertex, p->vertex, 2);
    
            return distanceA < distanceB; });

        // Initialize Lp !!!!Might be Neighbours class
        vector<Edge *> Lp = initializeLp(Rp, p);

        // Loop
        bool condition = true;
        Edge *rCandidate = nullptr;
        for (Edge *r : Rp)
        {
            rCandidate = r;

            if (find(Lp.begin(), Lp.end(), r) != Lp.end())
            {
                continue; // r is already in Lp
            }

            for (Edge *t : Lp)
            {
                if (isLongestEdgeInTriangle(*r, *t, r->destination, t->destination))
                {
                    condition = false;
                    break;
                }
            }

            if (!condition)
            {
                break;
            }
        }

        if (condition)
        {
            // Insert MRNG Edge (pr)
            if (rCandidate != nullptr)
            {

                MRNGEdge *prEdge = new MRNGEdge(p, rCandidate->destination, rCandidate->distance);
                resultEdges.push_back(prEdge);
            }
        }
    }

    return resultEdges;
}

void Graph::connectMRNGEdges(vector<MRNGEdge *> edges)
{

    for (size_t i = 0; i < edges.size(); ++i)
    {

        Edge *e = new Edge(edges[i]->destination, edges[i]->distance);
        edges[i]->source->MRNGNeighbourVertices.push_back(e);
    }
}

vector<Neighbour *> Graph::searchOnGraph(ImageVector *query, int k)
{

    // Using BFS

    vector<Neighbour *> NearestNeighbours;

    vector<bool> visited(this->vertices.size(), false);
    queue<Vertex *> queue;

    Vertex *navNode = nullptr;
    // Use Navigation Node as starting point
    for (Vertex *node : vertices)
    {

        if (node->vertex->id == this->NavNode)
        {

            navNode = node;
        }
    }
    if (navNode == nullptr)
    {
        cout << "NavNode not found!" << endl;
        return {};
    }

    queue.push(navNode);
    visited[navNode->vertex->id] = true;

    while (!queue.empty())
    {

        Vertex *currentVertex = queue.front();
        queue.pop();

        // Add current vertex to nearest neighbours
        double dist = calculateEuclideanDistance(currentVertex->vertex, query, 2);
        Neighbour *n = new Neighbour;
        n->id = currentVertex->vertex->id;
        n->distance = dist;
        NearestNeighbours.push_back(n);

        // Stop if we get k neighbours
        if (static_cast<int>(NearestNeighbours.size()) >= k)
        {
            break;
        }

        // Explore neighbors
        for (Edge *neighbor : currentVertex->MRNGNeighbourVertices)
        {
            if (!visited[neighbor->destination->vertex->id])
            {
                visited[neighbor->destination->vertex->id] = true;

                queue.push(neighbor->destination);
            }
        }
    }

    sort(NearestNeighbours.begin(), NearestNeighbours.end(), compareNeighbourDist);

    // cout<<"Printing Neighbours before returning"<<endl;
    // for (const auto& neigh : NearestNeighbours) {
    //     cout << "Neighbour with id: "<< neigh->id<<" and distance "<< neigh->distance<<endl;

    // }

    return vector<Neighbour *>(NearestNeighbours.begin(), NearestNeighbours.begin() + min(k, static_cast<int>(NearestNeighbours.size())));
}

void Graph::setNavNode(int nodeID)
{

    this->NavNode = nodeID;
}

int Graph::getNavNode()
{
    return this->NavNode;
}

vector<Vertex *> Graph::getVertices()
{
    return this->vertices;
}

void Graph::printGraph()
{

    cout << "Print Graph" << endl;
    for (const auto &vertex : this->vertices)
    {
        cout << "Vertex " << vertex->vertex->id << " ->";
        vertex->displayVertex();
    }
}

void Graph::printGraphMRNG()
{

    for (const auto &vertex : this->vertices)
    {
        cout << "Vertex " << vertex->vertex->id << " ->";
        vertex->displayVertexMRNG();
    }
}

Graph::~Graph()
{

    for (Vertex *vertex : this->vertices)
    {
        delete vertex;
    }

    this->vertices.clear();
}