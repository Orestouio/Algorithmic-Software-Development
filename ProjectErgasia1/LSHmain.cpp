#include <iostream>
#include <fstream>
#include <chrono>

#include "ImageVector.h"
#include "HashTableLSH.h"
#include "Functions.h"
#include "comFunctions.h"
#include "exitFunctions.h"

using namespace std;

int main(int argc, char *argv[])
{

	auto start = std::chrono::high_resolution_clock::now();
	CommandLineArgsLsh args = parseCommandLineArgsLsh(argc, argv);

	// verification that the input command are read correctly
	cout << "Input File: " << args.inputFile << endl;
	cout << "Query File: " << args.queryFile << endl;
	cout << "k: " << args.k << endl;
	cout << "L: " << args.L << endl;
	cout << "Output File: " << args.outputFile << endl;
	cout << "Number of Nearest: " << args.numNearest << endl;
	cout << "Radius: " << args.radius << endl;

	// File path
	string images_file = args.inputFile;
	string query_file = args.queryFile;

	// Read images
	vector<ImageVector> images = readImages(images_file); // Reading size = images/2

	// test for functionallity of exitFile class
	ExitFile output = ExitFile();

	// Number of images
	int image_count = num_images; // Number of images we read
	//cout << image_count << endl;
	// Create Array of pointers to Hash Tables
	Hash_Table_LSH **Hash_Tables_Array;
	Hash_Tables_Array = CreateHashTables(args.L, args.k);
	// Inserting image items to Hash Tables
	for (int i = 0; i < args.L; i++)
	{
		for (int j = 0; j < (image_count / 1000); j++)
		{
			Hash_Tables_Array[i]->InsertItem(&images[j]);
		}
	}

	cout << endl;
	cout << endl;

	// Read Query File and save queries in vector
	vector<ImageVector> queries = readQuery(query_file); // Reading size = queries/2

	int queryCount = 10; /// num_imagesQ; // Number of queries to be examined

	for (int i = 0; i < args.L; i++)
	{
		for (int j = 0; j < queryCount; j++)
		{
			Hash_Tables_Array[i]->FakeInsert(&queries[j]);
		}
	}

	vector<Neighbour> Rneighbours;

	// Find neighbours with LSH
	for (int j = 0; j < queryCount; j++)
	{
		// Check each bucket the query hashed into
		for (int i = 0; i < args.L; i++)
		{

			// find neighbours for test image with Range Search
			// Rneighbours = Hash_Tables_Array[i]->RangeSearch(&queries[j],args.radius,args.numNearest);
			Rneighbours = Hash_Tables_Array[i]->LSHnn(&queries[j], args.numNearest);
		}

		// Storing only N top neighbours
		queries[j].neighbours.clear();
		for (const Neighbour &neighbour : Rneighbours)
		{
			// cout<<neighbour.id<<": "<<neighbour.distance<<endl;
			queries[j].addNeighbour(neighbour.id, neighbour.distance);
		}
	}

	// Get the current time after the code
	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	int timeLSH = duration.count();
	std::cout << "Time taken by LSH: " << timeLSH << " microseconds" << std::endl;

	// Brute force
	//  Start a new timer
	start = std::chrono::high_resolution_clock::now();

	cout << "Starting Brute Force search, this might take a bit of time, please wait!" << endl;

	for (int q = 0; q < queryCount; q++)
	{
		cout << endl;
		cout << "Neighbours for query " << q << endl;
		vector<NeighbourBrute> nearestNeighbors;
		nearestNeighbors = BruteForce(&queries[q], images, args.radius, Rneighbours.size());

		int count1 = 0;
		for (NeighbourBrute &neigh : nearestNeighbors)
		{
			int count2 = 0;

			for (int el = 0; el < args.numNearest; el++)
			{
				if (count1 == count2)
				{
					cout << "LSH: " << queries[q].neighbours[el].id << " distance: " << queries[q].neighbours[el].distance << "  BruteForce: " << neigh.id << " distance:" << neigh.distance << endl;
					output.addNeighbor(q, queries[q].neighbours[el].id, queries[q].neighbours[el].distance, neigh.distance);
				}
				count2++;
			}

			count1++;
		}
		cout << endl;
	}
	// Record the stop time again
	stop = std::chrono::high_resolution_clock::now();
	// Calculate the duration for the second part
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	int timeBrute = duration.count();
	std::cout << "Time taken by BruteForce: " << timeBrute << " microseconds" << std::endl;

	/// Range Search

	// Find neighbours with Range Search
	for (int j = 0; j < queryCount; j++)
	{
		// Check each bucket the query hashed into
		for (int i = 0; i < args.L; i++)
		{

			// find neighbours for test image with Range Search
			Rneighbours = Hash_Tables_Array[i]->RangeSearch(&queries[j], args.radius, args.numNearest);
		}

		// Storing only N top neighbours
		queries[j].neighbours.clear();
		for (const Neighbour &neighbour : Rneighbours)
		{
			// cout<<neighbour.id<<": "<<neighbour.distance<<endl;
			queries[j].addNeighbour(neighbour.id, neighbour.distance);
		}
	}

	// Destroy Tables

	for (int i = 0; i < args.L; i++)
	{
		delete Hash_Tables_Array[i];
	}

	delete[] Hash_Tables_Array;

	// creating output file
	output.createFile(timeLSH, timeBrute, args.outputFile, true);
	return 0;
}
