#ifndef KMEANS_Headers
#define KMEANS_Headers
#include <list>
#include <vector>
#include <string>

#include "ImageVector.h"
#include "Cluster.h"
//#include "Functions.h"

using namespace std;

class Kmeans{

private:
    
    	//Vector of Clusters
	Cluster** ClustersVector;
	
	//Number of clusters
	int numberOfClusters;
	
	//Minimum distances
	double* minDistance;
    

    

public:
	// Constructor
	Kmeans(int);
	
	void InitializationKmeansPlusPlus(vector<ImageVector>&, int);
	void LoydMethod(vector<ImageVector>&, int);
	void reverseSearch(vector<ImageVector>&, int,string);
	void MacQueenMethod(vector<ImageVector>&, int);
	void Silhouette(int);
	void printClusters();
	void printCentroids();
	


	
	
	~Kmeans();
};

#endif
