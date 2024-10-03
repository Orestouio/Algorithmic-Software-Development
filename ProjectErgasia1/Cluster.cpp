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

//Cluster constructor
Cluster::Cluster(ImageVector* v, int id){

	this->centroid = v;
	this->centroidId = -1;
	this->clusterId = id;
	
		cout<<"Cluster created"<<endl;

}


Cluster::~Cluster(){}
