#ifndef CLUSTER_Headers
#define CLUSTER_Headers
#include <list>
#include <vector>

#include "ImageVector.h"
// #include "Functions.h"

using namespace std;

class Cluster
{

public:
	// Centroid
	ImageVector *centroid;
	int centroidId;

	// Cluster elements
	vector<ImageVector> clusterElements;

	// cluster id
	int clusterId;

	// Constructor
	Cluster(ImageVector *, int);
	void printClusterDetails();

	~Cluster();
};

#endif
