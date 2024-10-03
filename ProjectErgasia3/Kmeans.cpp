#include <iostream>
#include <random>
#include <list>
#include <numeric>
#include <string>
#include <bitset>
#include <chrono>
#include <algorithm>
#include <vector>
#include <limits>

#include "ImageVector.h"
#include "Kmeans.h"
#include "Cluster.h"
#include "ClusterFunctions.h"

using namespace std;

// Kmeans constructor
Kmeans::Kmeans(int clusters)
{

	this->numberOfClusters = clusters;

	// Keep min distance for every data point
	// minDistance = new double[10];

	// Create array of clusters(clusters)
	ClustersVector = new Cluster *[numberOfClusters];
	for (int i = 0; i < numberOfClusters; i++)
	{
		// Create Clusters
		ClustersVector[i] = new Cluster(NULL, i);
	}

	cout << "Kmeans algorithm called" << endl;
}

void Kmeans::InitializationKmeansPlusPlus(vector<ImageVector> &Images, int size)
{

	// Vector with pointers to clusters
	// vector<Cluster*> Clusters ;

	// centroid counter
	int t = 0;

	// sum = 0;

	// Vector to store centroids
	vector<ImageVector> centroids;

	// Array to store distances
	double DistArray[size] = {-1}; // Initialize all elements with -1

	// Initialize generator
	random_device rd;
	mt19937 gen(rd());

	// Use of std::uniform_int_distribution template
	uniform_int_distribution<int> distribution(0, size - 1);

	// Generate random uniform dist values
	int randomValue = distribution(gen);

	// Choose centroid uniformy at random for t=1
	centroids.push_back(Images[randomValue]);
	t++;

	// Find the rest of the centroids
	while (t != this->numberOfClusters)
	{

		// Initialize max D(i)
		double maxMinDistance = -1.0;

		// Check every data point
		for (int i = 0; i < size; i++)
		{

			// check if current data point is already centroid
			bool centroidFlag = false;
			for (int j = 0; j < t; j++)
			{
				if (Images[i].id == centroids[j].id)
				{
					centroidFlag = true;
				}
			}

			if (centroidFlag)
			{
				// If data point is centroid we store non valid distance
				DistArray[i] = -1;
				continue;
			}

			double minDist = numeric_limits<double>::max();
			for (int j = 0; j < t; j++)
			{
				double distance = calculateEuclideanDistance(&Images[i], &centroids[j]);

				if (distance < minDist)
					minDist = distance;
			}

			// Store minimum distance for data point i
			DistArray[i] = minDist;

			// Calculate maximum minimum distance
			if (minDist > maxMinDistance)
				maxMinDistance = minDist;
		}

		// Create P array
		double *P;
		int pSize = size - t;
		P = new double[pSize];
		int pcount = 0;

		// Vector to store data points that correspond to P distances
		vector<ImageVector> ObjectsInP;

		double sum = 0;
		for (int i = 0; i < size; i++)
		{

			// Check if element is already centroid
			if (DistArray[i] == -1)
				continue;

			// Normalize D(i) by dividing with maximum minimum distance
			DistArray[i] = DistArray[i] / maxMinDistance;

			// D(i)^2
			double finalDistance = pow(DistArray[i], 2);

			sum += finalDistance;

			P[pcount] = sum;

			// Add object in p vector
			ObjectsInP.push_back(Images[i]);
			pcount++;
		}

		// Use of std::uniform_real_distribution template
		uniform_real_distribution<double> distribution(0, sum);

		// Get x
		double x = distribution(gen);

		// Perform binary Search to find r
		int r = binarySearch(P, pSize, x);

		// New centroid found
		centroids.push_back(ObjectsInP[r]);
		// Add centroid
		t++;

		// delete arrays and vectors
		delete[] P;
		ObjectsInP.clear();
	}

	for (int c = 0; c < numberOfClusters; c++)
	{
		ImageVector *cent = new ImageVector(centroids[c]); // Use the copy constructor

		ClustersVector[c]->centroid = cent;
	}
	// cout<<"Printing Centroids Vector"<<endl;
	// int count =0;
	// for(int o; o<centroids.size(); o++){
	// 		for(int p=0; p<784; p++){
	// 			cout<<(int)centroids[o].pixels[p]<<" ";
	// 			count++;
	// 			if(count==28){
	// 				cout<<endl;
	// 				count=0;
	// 			}
	// 		}
	// }
	//  cout<<"Printing Centroids Init"<<endl;
	// int coun =0;
	// for(int o; o<numberOfClusters; o++){
	// 		for(int p=0; p<784; p++){
	// 			cout<<(int)ClustersVector[o]->centroid->pixels[p]<<" ";
	// 			coun++;
	// 			if(coun==28){
	// 				cout<<endl;
	// 				coun=0;
	// 			}
	// 		}
	// }
}

void recalculateCentroid(Cluster *cluster)
{
	if (cluster->clusterElements.empty())
	{
		// Handle the case where a cluster might end up with no elements
		cout << "Cluster " << cluster->clusterId << " has no elements." << endl;
		return;
	}

	int dimension = cluster->centroid->size; // Assuming 'size' is the number of dimensions
	vector<double> sum(dimension, 0.0);		 // Initialize sum of all dimensions to 0

	// Summing up all points in the cluster
	for (const ImageVector &image : cluster->clusterElements)
	{
		for (int i = 0; i < dimension; i++)
		{
			sum[i] += image.pixels[i];
		}
	}

	// Calculating the average for each dimension
	for (int i = 0; i < dimension; i++)
	{
		// Temporarily store the new centroid values in a higher precision type
		double newCentroidValue = sum[i] / cluster->clusterElements.size();
		// Cast the new centroid values back to unsigned char for storage
		cluster->centroid->pixels[i] = static_cast<unsigned char>(newCentroidValue);
	}
}

bool isConverged(const vector<unsigned char> &oldCentroid, const vector<unsigned char> &newCentroid, double threshold)
{
	double sum = 0.0;
	for (size_t i = 0; i < oldCentroid.size(); i++)
	{
		sum += pow(static_cast<double>(newCentroid[i]) - static_cast<double>(oldCentroid[i]), 2);
	}
	return sqrt(sum) < threshold;
}

void Kmeans::LoydMethod(vector<ImageVector> &Images, int size)
{
	bool converged = false;
	int maxIterations = 100; // Adjust as needed
	double threshold = 0.01; // Convergence threshold

	for (int iter = 0; iter < maxIterations && !converged; iter++)
	{
		// cout << "Iteration " << iter + 1 << endl; //////////////////////////////////////////////////
		//  Assign points to the nearest cluster
		for (int i = 0; i < size; i++)
		{
			double minDist = numeric_limits<double>::max();
			int closestClusterId = -1;
			for (int j = 0; j < numberOfClusters; j++)
			{
				double distance = calculateEuclideanDistance(&Images[i], ClustersVector[j]->centroid);
				if (distance < minDist)
				{
					minDist = distance;
					closestClusterId = j;
				}
			}
			ClustersVector[closestClusterId]->clusterElements.push_back(Images[i]);
		}

		// Recalculate centroids and check for convergence
		converged = true;
		for (int j = 0; j < numberOfClusters; j++)
		{
			vector<unsigned char> oldCentroid = ClustersVector[j]->centroid->pixels;
			recalculateCentroid(ClustersVector[j]);
			vector<unsigned char> newCentroid = ClustersVector[j]->centroid->pixels;

			if (!isConverged(oldCentroid, newCentroid, threshold))
			{
				converged = false;
				// cout << "Cluster " << j << ": Centroid not converged yet." << endl;/////////////////////////////////
			}
			else
			{
				// cout << "Cluster " << j << ": Centroid converged." << endl;/////////////////////////////////////
			}
			ClustersVector[j]->clusterElements.clear(); // Clear for next iteration
		}
	}

	// cout << "Iteration " << iter + 1 << endl; //////////////////////////////////////////////////
	//  Assign points to the nearest cluster
	for (int i = 0; i < size; i++)
	{
		double minDist = numeric_limits<double>::max();
		int closestClusterId = -1;
		for (int j = 0; j < numberOfClusters; j++)
		{
			double distance = calculateEuclideanDistance(&Images[i], ClustersVector[j]->centroid);
			if (distance < minDist)
			{
				minDist = distance;
				closestClusterId = j;
			}
		}
		ClustersVector[closestClusterId]->clusterElements.push_back(Images[i]);
	}
}

void Kmeans::MacQueenMethod(vector<ImageVector> &Images, int size)
{
	cout << "Starting MacQueen's Method..." << endl;

	// Loop over each image
	for (ImageVector &image : Images)
	{
		double minDist = numeric_limits<double>::max();
		int closestClusterIndex = -1;

		// Find the closest cluster for each image
		for (int j = 0; j < numberOfClusters; j++)
		{
			double distance = calculateEuclideanDistance(&image, ClustersVector[j]->centroid);
			if (distance < minDist)
			{
				minDist = distance;
				closestClusterIndex = j;
			}
		}

		// Assign the image to the closest cluster
		Cluster *closestCluster = ClustersVector[closestClusterIndex];
		closestCluster->clusterElements.push_back(image);

		// Update the centroid incrementally here
		ImageVector *centroid = closestCluster->centroid;
		int n = closestCluster->clusterElements.size(); // Number of elements in the cluster

		// cout << "Updating Centroid for Cluster " << closestClusterIndex << endl;
		for (int k = 0; k < image.size; k++)
		{
			// Incremental update of the centroid
			centroid->pixels[k] = centroid->pixels[k] + (image.pixels[k] - centroid->pixels[k]) / n;
			// cout << (int)centroid->pixels[k] << " "; // Debug: Print updated pixel value
		}
		// cout << endl;

		// No need to recalculate the entire centroid from scratch
	}

	cout << "MacQueen's Method Completed. Final Centroids:" << endl;
	for (int i = 0; i < numberOfClusters; i++)
	{
		// cout << "Centroid " << i << ": ";
		for (int k = 0; k < ClustersVector[i]->centroid->size; k++)
		{
			// cout << (int)ClustersVector[i]->centroid->pixels[k] << " ";
		}
		// cout << endl;
	}

	// After the loop, centroids are updated incrementally
	// and clusters have the newly assigned images
}

void Kmeans::reverseSearch(vector<ImageVector> &Images, int size, string)
{
}

void Kmeans::Silhouette(int size)
{
}

void Kmeans::printCentroidsAndClusterElements()
{
	cout << "Centroids and Cluster Elements: " << endl;
	for (int i = 0; i < numberOfClusters; i++)
	{
		cout << "Cluster " << i << ": Centroid = " << ClustersVector[i]->centroid << endl;

		cout << "Cluster Elements (Image IDs): ";
		for (auto &imageVector : ClustersVector[i]->clusterElements)
		{
			cout << imageVector.id << " ";
		}
		cout << endl
			 << endl;
	}
}

void Kmeans::printKmeansDetails()
{
	cout << "Number of Clusters: " << numberOfClusters << endl;
	printClusters(); // Assuming this method prints detailed information about each cluster
	printCentroids();
}

void Kmeans::printClusters()
{
	for (int i = 0; i < numberOfClusters; i++)
	{
		cout << "Cluster " << ClustersVector[i]->clusterId << endl;
		for (int j = 0; j < (int)ClustersVector[i]->clusterElements.size(); j++)
		{
			cout << ClustersVector[i]->clusterElements[j].id << endl;
		}
	}
}

void Kmeans::printCentroids()
{
	cout << "Centroids: " << endl;
	for (int i = 0; i < numberOfClusters; i++)
	{
		cout << "Cluster " << i << ": " << ClustersVector[i]->centroid->id;
		cout << " Pixels: ";
		for (auto pixel : ClustersVector[i]->centroid->pixels)
		{
			cout << static_cast<int>(pixel) << " ";
		}
		cout << endl;
	}
}

Kmeans::~Kmeans()
{

	delete[] ClustersVector;
}

void Kmeans::Silhouette()
{
	double totalSilhouette = 0.0;
	int totalPoints = 0;

	for (int i = 0; i < this->numberOfClusters; i++)
	{
		Cluster *cluster = ClustersVector[i];
		for (ImageVector &image : cluster->clusterElements)
		{
			// cout << "Got in LOOP " << endl;
			double a = calculateAverageDistance(image, cluster);
			double b = calculateMinimumAverageDistance(image);
			double silhouette = (b - a) / max(a, b);
			// cout << "For image we have a = " << a << " and b = " << b << " and Silhouette =  " << silhouette << endl;
			totalSilhouette += silhouette;
		}
		totalPoints += cluster->clusterElements.size();
		// cout << "In i = " << i << " we have totalpoints = " << totalPoints << endl;
	}

	double averageSilhouette = totalPoints > 0 ? totalSilhouette / totalPoints : 0;
	cout << "Average Silhouette Coefficient: " << (double)averageSilhouette << endl;
}

double Kmeans::calculateAverageDistance(ImageVector &image, Cluster *cluster)
{
	double sumDistance = 0.0;
	int size = cluster->clusterElements.size();
	// cout << "Got in calculate Average" << endl;
	for (ImageVector element : cluster->clusterElements)
	{
		// cout << "Got in LOOP calculate Average" << endl;
		if (image.id != element.id)
		{
			// cout << "Got in IF in LOOP calculate Average" << endl;
			sumDistance += calculateEuclideanDistance(&image, &element);
		}
	}

	return size > 1 ? sumDistance / (size - 1) : 0;
}

double Kmeans::calculateMinimumAverageDistance(ImageVector &image)
{
	double minDistance = numeric_limits<double>::max();
	// cout << "Got in calculate Minimum Average" << endl;
	for (int i = 0; i < numberOfClusters; i++)
	{
		// cout << "Got in LOOP calculate Minimum Average" << endl;
		Cluster *cluster = ClustersVector[i];
		if (find(cluster->clusterElements.begin(), cluster->clusterElements.end(), image) == cluster->clusterElements.end())
		{
			// cout << "Got in IF in LOOP calculate Average" << endl;
			double distance = calculateAverageDistance(image, cluster);
			if (distance < minDistance)
			{
				// cout << "Got in IF in IF in LOOP calculate Average" << endl;
				minDistance = distance;
			}
		}
	}
	return minDistance;
}

ImageVector Kmeans::findOriginalImageById(const vector<ImageVector> &originalData, int id)
{
	// Iterate through the originalData to find the image with the given id
	for (const auto &image : originalData)
	{
		if (image.id == id)
		{
			return image;
		}
	}
	// Handle case where the image is not found (can depend on how you want to manage this scenario)
}

double Kmeans::calculateAverageDistance(const ImageVector &image, const Cluster *cluster, const vector<ImageVector> &originalData)
{
	double sumDistance = 0.0;
	int size = cluster->clusterElements.size();

	for (const auto &element : cluster->clusterElements)
	{
		if (image.id != element.id)
		{
			ImageVector originalElement = findOriginalImageById(originalData, element.id);
			// Convert const ImageVector to non-const pointer for calculateEuclideanDistance
			sumDistance += calculateEuclideanDistance(const_cast<ImageVector *>(&image), const_cast<ImageVector *>(&originalElement));
		}
	}

	return size > 1 ? sumDistance / (size - 1) : 0;
}

double Kmeans::calculateMinimumAverageDistance(const ImageVector &image, const vector<ImageVector> &originalData)
{
	double minDistance = numeric_limits<double>::max();

	for (int i = 0; i < numberOfClusters; i++)
	{
		Cluster *cluster = ClustersVector[i];
		if (find_if(cluster->clusterElements.begin(), cluster->clusterElements.end(), [&image](const ImageVector &element)
					{ return element.id == image.id; }) == cluster->clusterElements.end())
		{
			double distance = calculateAverageDistance(image, cluster, originalData);
			if (distance < minDistance)
			{
				minDistance = distance;
			}
		}
	}
	return minDistance;
}

double Kmeans::ModifiedSilhouette(vector<ImageVector> &originalData)
{
	double totalSilhouette = 0.0;
	int totalPoints = 0;

	for (int i = 0; i < this->numberOfClusters; i++)
	{
		Cluster *cluster = ClustersVector[i];
		for (ImageVector &reducedImage : cluster->clusterElements)
		{
			ImageVector originalImage = findOriginalImageById(originalData, reducedImage.id);

			double a = calculateAverageDistance(originalImage, cluster, originalData);
			double b = calculateMinimumAverageDistance(originalImage, originalData);
			double silhouette = (b - a) / max(a, b);

			totalSilhouette += silhouette;
		}
		totalPoints += cluster->clusterElements.size();
	}

	return totalPoints > 0 ? totalSilhouette / totalPoints : 0;
}
