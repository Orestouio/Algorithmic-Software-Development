#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

#include "ImageVector.h"
#include "Functions.h"
#include "Hypercube.h"
#include "comFunctions.h"
#include "exitFunctions.h"

using namespace std;





int main(int argc , char*argv[]) {



	
	CommandLineArgsCube args = parseCommandLineArgsCube(argc, argv);

    	// verification that the input command are read correctly
   	cout << "Input File: " << args.inputFile << endl;
    	cout << "Query File: " << args.queryFile << endl;
    	cout << "k: " << args.k << endl;
    	cout << "probes: " << args.probes << endl;
		cout << "M: " << args.M << endl;
    	cout << "Output File: " << args.outputFile << endl;
    	cout << "Number of Nearest: " << args.numNearest << endl;
    	cout << "Radius: " << args.radius << endl;

	// File path
	string images_file =  args.inputFile;
	string query_file = args.queryFile;
	
	// Read images
	vector<ImageVector> images = readImages(images_file);

	
	int w = 5;
	int imageSize = images.size();

	int numImages = num_images;
	auto start = std::chrono::high_resolution_clock::now();
	
	HyperCube obj(args.k,w,args.probes,args.M,args.numNearest,imageSize);
	
	
	//Insert Images in cube
	for(int i=0;i<numImages;i++){
	
		obj.InsertItem(&images[i]);
	}
	
	//obj.printTable();
	
    //Read Query File and save queries in vector
    vector<ImageVector> queries = readQuery(query_file);
    
	int queryCount = num_imagesQ/1000 ;
	
	for (int i = 0; i < queryCount; i++)
	{
		
			obj.FakeInsert(&queries[i]);
	}
    

	vector<Neighbour> Rneighbours;
    
    //Find neighbours with Cube 
    for(int j=0; j<queryCount; j++){
	
	
	//find neighbours for test image 
    Rneighbours = obj.CubeSearch(&queries[j], args.numNearest);
	
	//Storing only N top neighbours
	queries[j].neighbours.clear();
	for(const Neighbour& neighbour : Rneighbours){
		cout<<neighbour.id<<": "<<neighbour.distance<<endl;
		queries[j].addNeighbour(neighbour.id,neighbour.distance,NULL);
	}
		
	
	}
	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	int timeCube = duration.count();
    std::cout << "Time taken by Cube: " << timeCube << " microseconds" << std::endl;


	auto startb = std::chrono::high_resolution_clock::now();
	//Find neighbours with BruteForce
    for(int j=0; j<queryCount; j++){
	
	
	//find neighbours for test image 
    Rneighbours = obj.BruteForce(&queries[j], args.numNearest);
	
	
	//Storing only N top neighbours
	queries[j].neighbours.clear();
	for(const Neighbour& neighbour : Rneighbours){
		//cout<<neighbour.id<<": "<<neighbour.distance<<endl;
		queries[j].addNeighbour(neighbour.id,neighbour.distance,NULL);
	}
		
	
	}
	auto stopb = std::chrono::high_resolution_clock::now();

	auto durationb = std::chrono::duration_cast<std::chrono::microseconds>(stopb - startb);
	int timeBrute = durationb.count();
    std::cout << "Time taken by BruteForce: " << timeBrute << " microseconds" << std::endl;




    
    vector<Neighbour> neigh;
    // test for functionallity of exitFile class
	ExitFile output = ExitFile();
    //Find neighbours
	for (int i = 0; i < queryCount; i++)
	{

		//find neighbours for test image based on range
		neigh = obj.RangeSearch(&queries[i], args.radius, args.numNearest);
		
		int count1 = 0;
		
		for (const Neighbour& neighbour : Rneighbours)
		{
			int count2 = 0;

			for (int el = 0; el < args.numNearest; el++)
			{
				if (count1 == count2)
				{
					cout << "Cube: " << neighbour.id << " distance: " << neighbour.distance << "  BruteForce: " << queries[i].neighbours[el].id << " distance:" << queries[i].neighbours[el].distance << endl;
					output.addNeighbor(i, neighbour.id  , neighbour.distance, queries[i].neighbours[el].distance );
				}
				count2++;
			}

			count1++;
		}
		cout << endl;
		// creating output file
	output.createFile(timeCube, timeBrute, args.outputFile, false);

	}
	
		
	
    
    
    
    
   
    

    
   
   

    return 0;
}
