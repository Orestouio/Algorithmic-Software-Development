#include <iostream>
#include <fstream>
#include <vector>

#include "ImageVector.h"
#include "Functions.h"
#include "comFunctions.h"
#include "Cluster.h"
#include "Kmeans.h"

using namespace std;





int main(int argc , char*argv[]) {
	/*CommandLineArgsCluster  clust = parseCommandLineArgsCluster(argc,  argv);
    configFile info = parseCommandconfigFile(clust.configurationFile);
    cout << "number_of_clusters " << info.K << endl;
    cout << "number_of_vector_hash_tables" << info.L << endl;
    cout << "number_of_vector_hash_functions" << info.k_LSH << endl;
    cout << "max_number_M_hypercube" << info.M << endl;
    cout << "number_of_hypercube_dimensions" << info.k_HC << endl;
    cout << "number_of_probes" << info.proves << endl;*/
	
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
	string images_file =  args.inputFile;
	string query_file = args.queryFile;
	
	// Read images
	vector<ImageVector> images = readImages(images_file);

	
	
	
	
	
	
    
    	cout<<"Clustering......"<<endl;
    	
    	Kmeans obj(3);
    	obj.InitializationKmeansPlusPlus(images,images.size());
		cout<<"Printing Clusters"<<endl;
		obj.printClusters();
		obj.LoydMethod(images,images.size());
		cout<<"Printing Clusters After Loyd"<<endl;
		obj.printClusters();
		obj.printCentroids();
		obj.MacQueenMethod(images,images.size());
		obj.printCentroids();
		//obj.printClusters();

		
    
    
    
    //Read Query File and save queries in vector
    vector<ImageVector> queries = readQuery(query_file);
    
    //obj.InsertItem(&queries[0]);
    //obj.FindNeighbours(&queries[0]);
    
    //queries[0].sortNeighbours();
    	//cout<<endl;
	//queries[0].printNeighbours(4);
	//cout<<endl;
    
	
	//for (int i = 0; i < 4; i++)
	//{
		
	//		obj.FakeInsert(&queries[i]);
	//}
    
    
    
    
    //Find neighbours
	//for (int i = 0; i < 4; i++)
	//{
        	
	//	cout<<"Query: "<<i<<endl;
		//find neighbours for test image
	//	obj.RangeSearch(&queries[i], 10000, 3);
		//queries[i].sortNeighbours();
    		//cout<<endl;
		//queries[i].printNeighbours(4);
		//cout<<endl;
        	
	//}
	
	
    
    
    
    
   
    
    //Destroy Tables
    
   /*for (int i =0; i<numberOfHashTables; i++){
   
   	delete Hash_Tables_Array[i];
   }
   
   delete[] Hash_Tables_Array;*/
   

    return 0;
}
