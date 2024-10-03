#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <cstring>
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

void ExitFile::createFile(int timeLsh, int timetrue, string file, bool lsh)
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
            if (lsh)
            {
                outputFile << "distanceLSH: " << neig.distanceLSH << std::endl;
            }
            else
            {
                outputFile << "sidtanceCube: " << neig.distanceLSH << std::endl;
            }
            outputFile << "distanceTrue: " << neig.distanceTrue << std::endl;
            i++;
        }

        // Write time information
        if (lsh)
        {
            outputFile << "tLSH: " << std::fixed << this->tLSH << std::endl;
        }
        else
        {
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

Exit2::Exit2(int count, int querry, int n, int m) : file(count), imageNumber(querry), N(n), saved(0), M(m)
{
    NeighboursFound.reserve(N);
}

bool Exit2::addNeig(int n, double appr, double trueT)
{
    Neigh newNeigh;
    newNeigh.Number = n;
    newNeigh.approximate = appr;
    newNeigh.distanceTrue = trueT;
    if (!saved)
    {
        MAF = newNeigh.distanceTrue / newNeigh.approximate;
    }
    if (saved < N)
    {
        NeighboursFound.push_back(newNeigh);
        saved++;
        return true;
    }
    else
    {
        printf("Warning: tried to input neighbour in full file\n");
        return false;
    }
}

Exit2::~Exit2()
{
    // cout << "Object Exit2 was deleted" << endl;
}

ExitFile2::ExitFile2(string filename, int q) : quees(q)
{
    Filename = filename;
}

bool ExitFile2::addQ(int count, int Q, int n, int m)
{
    Exit2 outPut = Exit2(count, Q, n, m);
    Querries.push_back(outPut);
    return true;
}

bool ExitFile2::addNeighQ(int count, int Q, int n, double appr, double real)
{
    while (Querries[Q].file != count)
    {
        Q += quees;
    }
    Querries[Q].addNeig(n, appr, real);
    return true;
}

bool ExitFile2::addTimes(int Q, int timeAP, int timeTr)
{
    Querries[Q].time = timeAP;
    Querries[Q].timeT = timeTr;
    return true;
}

void ExitFile2::createExit()
{
    // Open an output file for writing
    std::ofstream outputFile(Filename);
    if (!outputFile.is_open())
    {
        std::cerr << "Failed to open output file." << std::endl;
        return;
    }
    int timeApro = 0, timeTrue = 0, items = 0;
    double maf = 0;
    for (Exit2 &Ques : Querries)
    {
        Ques.createExit2(outputFile);
        timeApro += Ques.time;
        timeTrue += Ques.timeT;
        if (Ques.MAF > maf)
        {
            maf = Ques.MAF;
        }
        items++;
        outputFile << endl;
    }
    outputFile << endl;
    double t = timeApro / items;
    double t2 = timeTrue / items;
    outputFile << "tAverageApproximate: " << t << endl;
    outputFile << "tAverageTrue: " << t2 << endl;
    outputFile << "MAF : " << maf << endl;
    // Close the output file
    outputFile.close();

    std::cout << "Output file has been generated." << std::endl;
}

void Exit2::createExit2(std::ofstream &outputFile)
{

    if (this->M == 1)
    {
        outputFile << "GNNS Results" << endl;
    }
    else
    {
        outputFile << "MRNG Results" << endl;
    }
    // Write the query image number
    outputFile << "Query: " << this->imageNumber << std::endl;
    int i = 1;
    for (Neigh &Nei : NeighboursFound)
    {
        outputFile << "Nearest neighbor-" << i << " : " << Nei.Number << endl;
        outputFile << "distanceApproximate: " << Nei.approximate << endl;
        outputFile << "diastanceTrue: " << Nei.distanceTrue << endl;
        i++;
    }
}
