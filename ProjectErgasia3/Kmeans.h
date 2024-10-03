#ifndef KMEANS_Headers
#define KMEANS_Headers
#include <list>
#include <vector>
#include <string>

#include "ImageVector.h"
#include "Cluster.h"
// #include "Functions.h"

using namespace std;

class Kmeans
{

private:
	// Vector of Clusters
	Cluster **ClustersVector;

	// Number of clusters
	int numberOfClusters;

	// Minimum distances
	double *minDistance;

public:
	// Constructor
	Kmeans(int);

	void InitializationKmeansPlusPlus(vector<ImageVector> &, int);
	void LoydMethod(vector<ImageVector> &, int);
	void reverseSearch(vector<ImageVector> &, int, string);
	void MacQueenMethod(vector<ImageVector> &, int);
	void Silhouette(int);
	double ModifiedSilhouette(vector<ImageVector> &);
	ImageVector findOriginalImageById(const vector<ImageVector> &, int);
	double calculateAverageDistance(const ImageVector &, const Cluster *, const vector<ImageVector> &);
	double calculateMinimumAverageDistance(const ImageVector &, const vector<ImageVector> &);
	void printCentroids();
	void Silhouette();
	void printKmeansDetails();
	void printClusters();
	void printCentroidsAndClusterElements();
	~Kmeans();

private:
	double calculateAverageDistance(ImageVector &, Cluster *);
	double calculateMinimumAverageDistance(ImageVector &);
};

#endif
