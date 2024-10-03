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
	//minDistance = new double[10];

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
	while (t != this->numberOfClusters){

		// Initialize max D(i)
		double maxMinDistance = -1.0;

		// Check every data point
		for (int i = 0; i < size; i++){

			// check if current data point is already centroid
			bool centroidFlag = false;
			for (int j = 0; j < t; j++){
				if (Images[i].id == centroids[j].id){
					centroidFlag = true;
				}
			}

			if (centroidFlag){
				// If data point is centroid we store non valid distance
				DistArray[i] = -1;
				continue;
			}


		 	double minDist = numeric_limits<double>::max();
		 	for (int j = 0; j < t; j++){
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


		//Create P array
		double* P;
		int pSize = size - t;
		P = new double[pSize];
		int pcount =  0;

		//Vector to store data points that correspond to P distances
		vector<ImageVector> ObjectsInP;

		double sum = 0;
		for(int i=0; i<size; i++){

			//Check if element is already centroid
			if(DistArray[i] == -1)
				continue;

			//Normalize D(i) by dividing with maximum minimum distance
			DistArray[i] = DistArray[i] / maxMinDistance;

			//D(i)^2
			double finalDistance = pow(DistArray[i],2);

			sum += finalDistance;
			
			P[pcount] = sum;
			
			//Add object in p vector
			ObjectsInP.push_back(Images[i]);
			pcount++;

		}

		// Use of std::uniform_real_distribution template
		uniform_real_distribution<double> distribution(0, sum);

		// Get x
		double x = distribution(gen);


		//Perform binary Search to find r
		int r = binarySearch(P,pSize, x);
		
		
		//New centroid found
		centroids.push_back(ObjectsInP[r]);
		//Add centroid
		t++;


		//delete arrays and vectors
		delete[] P;
		ObjectsInP.clear();
		

		

	}
	
	for (int c = 0; c < numberOfClusters; c++) {
    ImageVector* cent = new ImageVector(centroids[c]);  // Use the copy constructor

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


void Kmeans::LoydMethod(vector<ImageVector> &Images, int size){

	for (int i = 0; i < size; i++){

		if(i==20)
			break;

		// check if current data point is already centroid
		bool centroidFlag = false;
		for (int j = 0; j < this->numberOfClusters; j++){
			if (Images[i].id == this->ClustersVector[j]->centroid->id){
				centroidFlag = true;
			}
		}
		

		if (centroidFlag){
			continue;
		}


		double minDist = numeric_limits<double>::max();
		int id = -1;
		
		for (int j = 0; j < numberOfClusters; j++){
			
		 	double distance = calculateEuclideanDistance(&Images[i], ClustersVector[j]->centroid);

			if (distance < minDist){
				minDist = distance;
				id = ClustersVector[j]->clusterId;
			}

		}
		
		ClustersVector[id]->clusterElements.push_back(Images[i]); 


	}
}

void Kmeans::MacQueenMethod(vector<ImageVector> &Images, int size){

	
	vector<ImageVector*> PreviousCentroids;
	vector<ImageVector*> CurrentCentroids;

	//bool terminateFlag = true;
	//int count = 0;
	int ImageSize = ClustersVector[0]->clusterElements[0].size;
	//while(terminateFlag){

	for(int i=0; i<numberOfClusters;i++){
		PreviousCentroids.push_back(ClustersVector[i]->centroid);
	}

	for(int i=0; i<numberOfClusters; i++){
		

		//double sum = 0;

		

		
		vector<double> result(ImageSize, 0.0);
		vector<unsigned char> resultFinal(ImageSize, 0);

		for(int j=0; j<(int)ClustersVector[i]->clusterElements.size(); j++){

				for(int k=0; k<ImageSize; k++){
        			result[k] = (result[k] + (ClustersVector[i]->clusterElements[j].pixels[k]));
				}
			
		}
		for(int k=0; k<ImageSize; k++){
        	result[k] = result[k] / ImageSize;
		}

		resultFinal = doublesToUnsignedChars(result);

		//-10 is id for mean centroids that are not actuall elements
		// ImageVector* centroid;
		
		// centroid = new ImageVector(ImageSize, -10);

		ClustersVector[i]->centroid->id = -10;
		
		 for(int k=0; k<ImageSize; k++){
        	ClustersVector[i]->centroid->pixels[k] = resultFinal[k];
		 }
		

		// ClustersVector[i]->centroid = centroid;
	
		
	}

	// for(int q=0; q<numberOfClusters; q++){
	// 	ClustersVector[q]->clusterElements.clear();
	// }
	// for (int i = 0; i < size; i++){
	// double minDist = numeric_limits<double>::max();
	// 	int id = -1;
		
	// 	for (int j = 0; j < numberOfClusters; j++){
			
	// 	 	double distance = calculateEuclideanDistance(&Images[i], ClustersVector[j]->centroid);

	// 		if (distance < minDist){
	// 			minDist = distance;
	// 			id = ClustersVector[j]->clusterId;
	// 		}

	// 	}
		
	//  	 	ClustersVector[id]->clusterElements.push_back(Images[i]); 
	//  }
	//LoydMethod(Images,size);
	// cout<<"Printing Centroids"<<endl;
	// int coun =0;
	// 	for(int i=0; i<numberOfClusters;i++){
	// 		for(int p=0; p<784; p++){
	// 			cout<<(int)ClustersVector[i]->centroid->pixels[p]<<" ";
	// 			coun++;
	// 			if(coun==28){
	// 				cout<<endl;
	// 				coun=0;
	// 			}
	// 		}
	// 	}
		
	// for(int i=0; i<numberOfClusters;i++){
	// 	CurrentCentroids.push_back(ClustersVector[i]->centroid);
	// }
	
	// cout<<"Check "<<count<<endl;
	// for(int i=0; i<numberOfClusters;i++){
		
	// 		int dist = calculateEuclideanDistance(PreviousCentroids[i], CurrentCentroids[i]);
	// 		cout<<PreviousCentroids[i]->id<< CurrentCentroids[i]->id<<endl;

	// 		if(dist != 0)
	// 			terminateFlag = true;
	// 		else	
	// 			terminateFlag = false;
	// }
		
		
	 

	// PreviousCentroids.clear();
	// CurrentCentroids.clear();

	// count++;
//}
}


void Kmeans::reverseSearch(vector<ImageVector> &Images, int size, string ){


}

void Kmeans::Silhouette(int size){


}


void Kmeans::printClusters(){

	for(int i=0;i<numberOfClusters;i++){
		cout<<"Cluster "<<ClustersVector[i]->clusterId<<endl;
		for(int j=0; j<(int)ClustersVector[i]->clusterElements.size();j++){
			cout<<ClustersVector[i]->clusterElements[j].id<<endl;
		}
	}

}

void Kmeans::printCentroids(){

	cout<<"Centroids: "<<endl;
	for(int i=0;i<numberOfClusters;i++){
		
		cout<<"Cluster "<<i<<": "<<ClustersVector[i]->centroid->id<<endl;
	}

}




Kmeans::~Kmeans()
{

	delete[] ClustersVector;
}
