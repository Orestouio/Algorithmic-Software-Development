#include <iostream>
#include <fstream>
#include <vector>

#include "ImageVector.h"
#include "Functions.h"
#include "comFunctions.h"
#include "Cluster.h"
#include "Kmeans.h"

using namespace std;

int main(int argc, char *argv[])
{
	CommandLineArgsCluster clust = parseCommandLineArgsCluster(argc, argv);
	cout << "Input File: " << clust.inputFile << endl;
	cout << "Configuration File: " << clust.configurationFile << endl;
	cout << "OutputFile File: " << clust.outputFile << endl;
	cout << "K : " << clust.K << endl;

	// File path
	string images_file = clust.inputFile;

	// Read images
	vector<ImageVector> images = readImages(images_file);

	cout << "Clustering......" << endl;

	Kmeans obj(clust.K);
	int imagenumbers = images.size() / 10;
	cout << "We have image size " << imagenumbers << endl;
	obj.InitializationKmeansPlusPlus(images, imagenumbers);
	cout << "Printing Starting Clusters" << endl;
	// obj.printClusters();
	// obj.printCentroids();
	obj.LoydMethod(images, imagenumbers);
	cout << "Printing Clusters After Loyd" << endl;
	// obj.printClusters();
	// obj.printCentroids();
	// obj.printCentroidsAndClusterElements();
	cout << "Finding Silhouette number for clusters" << endl;
	obj.Silhouette();
	// Read images
	// File path
	string imagesBig = "data.dat";
	vector<ImageVector> imagesOr = readImages(imagesBig);
	cout << "Starting the comparison" << endl;
	double j = obj.ModifiedSilhouette(imagesOr);
	cout << "We found " << j << endl;
	return 0;
}
