#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <cmath>
#include <random>
#include <climits>

#include "Functions.h"
#include "ImageVector.h"
#include "Vertex.h"
#include "Edge.h"
#include "Neighbour.h"

using namespace std;

class Vertex;
class Edge;

int magic_number, num_images, num_rows, num_cols;
int magic_numberQ, num_imagesQ, num_rowsQ, num_colsQ;

// Euclidean Mod for LSH G function
int euclidean_mod(int a, unsigned int b)
{
    int r = a % b;
    return r >= 0 ? r : r + b;
}

// Array seeder with Uniform Distribution values
int UniformDistributionGenerator(int vector_size)
{

    // cout<<"Entering Uniform Dist"<<endl;

    // Initialize generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<std::size_t> distribution(0, vector_size - 1);

    // Generate random uniform dist values
    int randomValue = distribution(gen);

    return randomValue;
}

Vertex *minElement(vector<Edge *> n, ImageVector *q)
{

    Vertex *minV = NULL;

    double min = numeric_limits<float>::max();
    for (Edge *edge : n)
    {
        double dist = calculateEuclideanDistance(q, edge->destination->vertex, 2);
        if (dist < min)
        {
            min = dist;
            minV = edge->destination;
        }
    }

    return minV;
}

ImageVector *FindNavNode(vector<Vertex *> vertices, ImageVector *avgDataPoint)
{

    ImageVector *navNode = nullptr;

    double min = numeric_limits<float>::max();

    for (Vertex *v : vertices)
    {

        double dist = calculateEuclideanDistance(avgDataPoint, v->vertex, 2);
        if (dist < min)
        {
            min = dist;
            navNode = v->vertex;
        }
    }

    return navNode;
}

ImageVector *calculateCentroid(vector<ImageVector> &images)
{
    int numPixels = 28 * 28;
    int numImages = num_images;

    vector<unsigned int> sumVector(numPixels, 0);
    for (const ImageVector &img : images)
    {
        const vector<unsigned char> &imgPixels = img.pixels;
        for (size_t i = 0; i < imgPixels.size(); ++i)
        {
            sumVector[i] += static_cast<unsigned int>(imgPixels[i]);
        }
    }

    vector<unsigned char> CentroidVector(sumVector.size(), 0);
    for (int i = 0; i < numPixels; ++i)
    {
        CentroidVector[i] = static_cast<unsigned char>(sumVector[i] / numImages);
    }

    ImageVector *centImage = new ImageVector(numPixels, -1);
    centImage->pixels = CentroidVector;
    return centImage;
}

bool isVertexInVector(Vertex *targetVertex, const vector<Neighbour *> &S)
{
    // Iterate through the vector
    for (const Neighbour *n : S)
    {
        // Compare pointers to check if the ids are the same
        if (targetVertex->vertex->id == n->id)
        {
            return true; // if target vertex found
        }
    }
    return false; // target vertex not found
}

vector<Edge *> initializeLp(const vector<Edge *> Rp, Vertex *p)
{

    vector<Edge *> Lp;

    if (!Rp.empty())
    {
        double minDistance = Rp.front()->distance;

        for (Edge *edge : Rp)
        {
            double distance = edge->distance;
            if (distance == minDistance)
            {
                Lp.push_back(edge);
            }
            else
            {
                break;
            }
        }
    }

    return Lp;
}

bool isLongestEdgeInTriangle(Edge &pr, Edge &pt, Vertex *r, Vertex *t)
{
    // Calculate the distances
    double dist_pr = pr.distance;
    double dist_pt = pt.distance;
    double dist_rt = calculateEuclideanDistance(r->vertex, t->vertex, 2);

    // Check if pr is the longest edge
    return (dist_pr > dist_pt) && (dist_pr > dist_rt);
}

bool compareNeighbourDist(const Neighbour *a, const Neighbour *b)
{
    return a->distance < b->distance;
}

Hash_Table_LSH **CreateHashTables(int numberOfHashTables, int K, int imgnum)
{

    

    Hash_Table_LSH **Hash_Tables_Array = new Hash_Table_LSH *[numberOfHashTables];
    for (int i = 0; i < numberOfHashTables; i++)
    {
        // Create Hash Tables
        Hash_Tables_Array[i] = new Hash_Table_LSH(imgnum, K, 5, 784);
    }

    return Hash_Tables_Array;
}

void LSHtoGraph(Graph *G, int k, Hash_Table_LSH **Hash_Tables_Array, int HashTableNum, vector<ImageVector> &images, int queryCount)
{


    vector<ImageVector *> Kneighbours;

    for (int j = 0; j < queryCount; j++)
    {
        G->addVertex(&images[j]);
    }
    for (int j = 0; j < queryCount; j++)
    {

        // Check each bucket the query hashed into
        for (int i = 0; i < HashTableNum; i++)
        {

            // find neighbours for test image
            // Rneighbours = Hash_Tables_Array[i]->RangeSearch(&queries[j],args.radius,args.numNearest);
            Kneighbours = Hash_Tables_Array[i]->LSHGraphnn(&images[j], k);
        }

        // Storing only N top neighbours
        images[j].neighbours.clear();
        for (ImageVector *neighbour : Kneighbours)
        {
            // cout<<neighbour.id<<": "<<neighbour.distance<<endl;
            if (images[j].id != neighbour->id)
            {
                // queries[j].addNeighbour(neighbour.id, neighbour.distance);
                G->addVertexNeighbour(&images[j], neighbour);
            }
        }
    }
}

// Calculate Euclidean Distance
double calculateEuclideanDistance(ImageVector *query, ImageVector *dataImage, int n)
{

    double distance = 0.0;

    for (int i = 0; i < query->size; i++)
    {
        double diff = (query->pixels[i]) - (dataImage->pixels[i]);
        distance += pow(diff, n);
    }
    return pow(distance, 1.0 / n);
}

// Function to find the nearest neighbors within a specified range
vector<NeighbourBrute> FindNearestNeighborsBruteForce(ImageVector *query, vector<ImageVector> &dataset, double R, int items)
{
    vector<NeighbourBrute> nearestNeighbors;
    // cout << "We have items: " << items << " , we also have R = " << R << endl;
    int count = 0;
    for (ImageVector &data : dataset)
    {

        double distance = calculateEuclideanDistance(query, &data, 2);

        if (distance <= R)
        {
            nearestNeighbors.emplace_back(data.id, distance);
            // cout << "We found id:" << data.id << " we find at distance: " << distance << endl;
        }
        count++;
    }

    // Sort the Neighbour vector by distance
    sort(nearestNeighbors.begin(), nearestNeighbors.end());

    // Resize the vector to contain at most 'items' neighbors
    if (nearestNeighbors.size() > static_cast<std::vector<NeighbourBrute>::size_type>(items))
    {
        nearestNeighbors.resize(items);
    }

    return nearestNeighbors;
}

vector<NeighbourBrute> BruteForce(ImageVector *queries, vector<ImageVector> &dataset, double R, int items)
{

    vector<NeighbourBrute> nearestNeighbors1, nearestNeighbors2;
    nearestNeighbors1 = FindNearestNeighborsBruteForce(queries, dataset, R, items); // Pass the query by pointer, dataset, R value
    if (nearestNeighbors2.empty())
    {
        swap(nearestNeighbors1, nearestNeighbors2);
    }
    else
    {
        nearestNeighbors2.insert(nearestNeighbors2.end(), nearestNeighbors1.begin(), nearestNeighbors1.end());
        // Sort the Neighbour vector by distance
        sort(nearestNeighbors2.begin(), nearestNeighbors2.end());

        // Resize the vector to contain at most 'items' neighbors
        if (nearestNeighbors2.size() > static_cast<std::vector<NeighbourBrute>::size_type>(items))
        {
            nearestNeighbors2.resize(items);
        }
    }
    return nearestNeighbors2;
}

//  Read data from binary file function
vector<ImageVector> readImages(const string &filename)
{
    ifstream file(filename, ios::binary);
    if (!file.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        exit(1);
    }

    // Vector to hold vector<Image> objects
    vector<ImageVector> images;

    // Read the header information
    file.read((char *)(&magic_number), sizeof(magic_number));
    file.read((char *)(&num_images), sizeof(num_images));
    file.read((char *)(&num_rows), sizeof(num_rows));
    file.read((char *)(&num_cols), sizeof(num_cols));

    // Convert to little endian
    magic_number = __builtin_bswap32(magic_number);
    num_images = __builtin_bswap32(num_images);
    num_rows = __builtin_bswap32(num_rows);
    num_cols = __builtin_bswap32(num_cols);

    for (int i = 0; i < num_images; ++i)
    {
        ImageVector image(num_rows * num_cols, i);

        // Read the pixel data
        file.read((char *)(image.pixels.data()), num_rows * num_cols);

        images.push_back(image);
    }

    file.close();
    return images;
}

//  Read data from query binary file
vector<ImageVector> readQuery(const string &filename)
{
    ifstream file(filename, ios::binary);
    if (!file.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        exit(1);
    }

    // Vector to hold vector<Image> objects
    vector<ImageVector> images;

    // Read the header information
    file.read((char *)(&magic_numberQ), sizeof(magic_numberQ));
    file.read((char *)(&num_imagesQ), sizeof(num_imagesQ));
    file.read((char *)(&num_rowsQ), sizeof(num_rowsQ));
    file.read((char *)(&num_colsQ), sizeof(num_colsQ));

    // Convert to little endian
    magic_numberQ = __builtin_bswap32(magic_numberQ);
    num_imagesQ = __builtin_bswap32(num_imagesQ);
    num_rowsQ = __builtin_bswap32(num_rowsQ);
    num_colsQ = __builtin_bswap32(num_colsQ);

    for (int i = 0; i < num_images; ++i)
    {
        ImageVector image(num_rows * num_cols, i);

        // Read the pixel data
        file.read((char *)(image.pixels.data()), num_rows * num_cols);

        images.push_back(image);
    }

    file.close();
    // cout<<"Number of test images "<<num_imagesQ<<endl;
    return images;
}
