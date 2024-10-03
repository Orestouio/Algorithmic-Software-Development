#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>

#include "ImageVector.h"
#include "exitFunctions.h"
using namespace std;

ExitFile::ExitFile()
{
    cout << "Object ExitFile was created" << endl;
}

ExitFile::~ExitFile()
{
    cout << "Object ExitFile was deleted" << endl;
}

void ExitFile::addNeighbor(int QueryNum, int number, double distanceLsh, double distancetrue)
{
    Neighbor neigbor;
    neigbor.imageNumber = number;
    neigbor.distanceLSH = distanceLsh;
    neigbor.distanceTrue = distancetrue;
    for (Query &query : Queries)
    {
        if (query.queryNumber == QueryNum)
        {
            query.neighbors.push_back(neigbor);
            return;
        }
    }
    Query newQ;
    newQ.queryNumber = QueryNum;
    newQ.neighbors.push_back(neigbor);
    this->Queries.push_back(newQ);
}

void ExitFile::createFile(int timeLsh, int timetrue, string file,bool lsh)
{

    this->tLSH = timeLsh;
    this->tTrue = timetrue;

    // Open an output file for writing
    std::ofstream outputFile(file);

    if (!outputFile.is_open())
    {
        std::cerr << "Failed to open output file." << std::endl;
        return;
    }

    for (Query &query : Queries)
    {
        // Write the query image number
        outputFile << "Query: " << query.queryNumber << std::endl;

        // Write nearest neighbors
        int i = 0;
        for (Neighbor &neig : query.neighbors)
        {
            outputFile << "Nearest neighbor-" << (i + 1) << ": " << neig.imageNumber << std::endl;
            if(lsh){
                outputFile << "distanceLSH: " << neig.distanceLSH << std::endl;
            }else{
                outputFile << "sidtanceCube: " << neig.distanceLSH << std::endl;
            }
            outputFile << "distanceTrue: " << neig.distanceTrue << std::endl;
            i++;
        }

        // Write time information
        if(lsh){
            outputFile << "tLSH: " << std::fixed << this->tLSH << std::endl;
        }else{
            outputFile << "tCube: " << std::fixed << this->tLSH << std::endl;
        }
        outputFile << "tTrue: " << std::fixed << this->tTrue << std::endl;

        // Write R-near neighbors
        outputFile << "R-near neighbors:" << std::endl;

        for (Neighbor &neig : query.neighbors)
        {

            outputFile << "image_number_" << neig.imageNumber << endl;
        }
    }
    // Close the output file
    outputFile.close();

    std::cout << "Output file has been generated." << std::endl;
}