#include <iostream>
#include <fstream>
#include <chrono>

#include "comFunctions.h"
#include "Graph.h"
#include "ImageVector.h"
#include "Functions.h"
#include "exitFunctions.h"

using namespace std;

int main(int argc, char *argv[])
{
    CommandLinesArgsGraph args = parseCommandLineArgsGraph(argc, argv);
    // verification that the input command are read correctly
    cout << "We have m: " << args.m << endl;
    cout << "Input File: " << args.inputFile << endl;
    cout << "Query File: " << args.queryFile << endl;
    cout << "k: " << args.k << endl;
    cout << "E: " << args.E << endl;
    cout << "R: " << args.R << endl;
    cout << "N: " << args.N << endl;
    cout << "I: " << args.I << endl;
    cout << "Output File: " << args.outputFile << endl;

    bool repeat = true;
    int count = 0;
    ExitFile2 *outPut = nullptr;
    int qToRead = 5;
    while (repeat)
    {
        // Ask and check if there is dataset, if not ask for it
        if (args.inputFile.empty())
        {
            cout << "Please insert the input File: ";
            cin >> args.inputFile;
            cout << "You have inserted " << args.inputFile << endl;
        }
        // Create search struct
        // Read input file
        string images_file = args.inputFile;
        Graph G;
        G.initializeGraph();

        vector<ImageVector> images = readImages(images_file);
        // Number of images
        int image_count = num_images / 600; // Number of images we read
        // cout << image_count << endl;
        //  Create Array of pointers to Hash Tables
        Hash_Table_LSH **Hash_Tables_Array;
        Hash_Tables_Array = CreateHashTables(10, args.k, image_count);
        int hashTableNum = 10;
        // Inserting image items to Hash Tables
        for (int i = 0; i < hashTableNum; i++)
        {
            for (int j = 0; j < (image_count); j++)
            {
                Hash_Tables_Array[i]->InsertItem(&images[j]);
            }
        }

        int neighboursLSH = args.k;
        LSHtoGraph(&G, neighboursLSH, Hash_Tables_Array, hashTableNum, images, image_count);

        // Ask and check if there is querry file and output file
        if (args.queryFile.empty())
        {
            cout << "Please insert the query File: ";
            cin >> args.queryFile;
            cout << "You have inserted " << args.queryFile << endl;
        }
        if (args.outputFile.empty())
        {
            cout << "Please insert the output File: ";
            cin >> args.outputFile;
            cout << "You have inserted " << args.outputFile << endl;
        }
        if (!count)
        {
            outPut = new ExitFile2(args.outputFile, qToRead);
        }
        vector<ImageVector> queries = readQuery(args.queryFile);
        if (args.m == 1)
        {
            for (int i = 0; i < qToRead; i++)
            {
                outPut->addQ(count, i, qToRead, args.m);
                auto start = std::chrono::high_resolution_clock::now();
                vector<Neighbour *> knn = G.GNN(&queries[i], args.R, qToRead, args.E, args.N);

                auto stop = std::chrono::high_resolution_clock::now();

                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                int time = duration.count();
                // brute
                start = std::chrono::high_resolution_clock::now();
                // Example how to call brute
                vector<NeighbourBrute> nearestNeighbors;
                nearestNeighbors = BruteForce(&queries[i], images, 3000, qToRead); // 2 Temporary, is K

                // Record the stop time again
                stop = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                int timeBrute = duration.count();
                ///

                int count1 = 0;
                for (const auto &neigh : knn)
                {
                    int count2 = 0;

                    for (NeighbourBrute &ngh : nearestNeighbors)
                    {
                        if (count1 == count2)
                        {
                            outPut->addNeighQ(count, i, neigh->id, neigh->distance, ngh.distance);
                        }
                        count2++;
                    }

                    count1++;
                }
                outPut->addTimes(i, time, timeBrute);
            }
        }
        else
        {
            for (int i = 0; i < qToRead; i++)
            {
                outPut->addQ(count, i, qToRead, args.m);
                auto start = std::chrono::high_resolution_clock::now();
                vector<MRNGEdge *> IndexEdges = G.constructIndex();
                ImageVector *centroid = calculateCentroid(images);
                ImageVector *nav = FindNavNode(G.getVertices(), centroid);
                G.setNavNode(nav->id);

                G.connectMRNGEdges(IndexEdges);

                vector<Neighbour *> nn = G.searchOnGraph(&queries[i], args.N);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                int time = duration.count();

                // brute
                start = std::chrono::high_resolution_clock::now();
                // Example how to call brute
                vector<NeighbourBrute> nearestNeighbors;
                nearestNeighbors = BruteForce(&queries[i], images, 3000, args.N); // 2 Temporary, is K

                // Record the stop time again
                stop = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                int timeBrute = duration.count();
                int count1 = 0;
                for (const auto &neigh : nn)
                {
                    int count2 = 0;

                    for (NeighbourBrute &ngh : nearestNeighbors)
                    {
                        if (count1 == count2)
                        {
                            outPut->addNeighQ(count, i, neigh->id, neigh->distance, ngh.distance);
                        }
                        count2++;
                    }

                    count1++;
                }
                outPut->addTimes(i, time, timeBrute);
            }
        }
        cout << "Would you like to restart? Type 'Y' for yes and 'N' for no" << endl;
        string answer;
        cin >> answer;
        if (answer == "Y")
        {
            cout << "Please insert the input File: ";
            cin >> args.inputFile;
            cout << "You have inserted " << args.inputFile << endl;
            cout << "Please insert the query File: ";
            cin >> args.queryFile;
            cout << "You have inserted " << args.queryFile << endl;
            count++;
        }
        else
        {
            repeat = false;
        }
    }
    outPut->createExit();
    if (outPut != nullptr)
    {
        delete outPut;    // Delete the dynamically allocated object
        outPut = nullptr; // Set pointer to nullptr after deleting
    }

    // Ask if you want to close the program or make an other search
    return 0;
}