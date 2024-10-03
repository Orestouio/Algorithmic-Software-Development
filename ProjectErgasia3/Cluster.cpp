#include <iostream>
#include <random>
#include <list>
#include <numeric>
#include <string>
#include <bitset>
#include <chrono>
#include <algorithm>

#include "ImageVector.h"
#include "Cluster.h"

using namespace std;

// Cluster constructor
Cluster::Cluster(ImageVector *v, int id)
{

	this->centroid = v;
	this->centroidId = -1;
	this->clusterId = id;

	cout << "Cluster created" << endl;
}

void Cluster::printClusterDetails()
{
	cout << "Cluster ID: " << clusterId << endl;
	cout << "Centroid ID: " << (centroid ? centroidId : -1) << endl;
	if (centroid)
	{
		cout << "Centroid Coordinates: ";
		for (int i = 0; i < centroid->size; ++i)
		{
			cout << static_cast<int>(centroid->pixels[i]) << " ";
		}
		cout << endl;
	}
	cout << "Number of Elements in Cluster: " << clusterElements.size() << endl;
	for (const auto &element : clusterElements)
	{
		cout << "ImageVector ID: " << element.id << ", Pixels: ";
		for (int i = 0; i < element.size; ++i)
		{
			cout << static_cast<int>(element.pixels[i]) << " ";
		}
		cout << endl;
	}
}

Cluster::~Cluster() {}
