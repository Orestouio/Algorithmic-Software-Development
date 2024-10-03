#include <iostream>
#include <random>
#include <list>
#include <numeric>
#include <string>
#include <bitset>
#include <chrono>
#include <algorithm>
#include <unordered_set>
#include <vector>

#include "Hypercube.h"
#include "ImageVector.h"
#include "DictionaryF.h"
#include "CubeFunctions.h"

using namespace std;

//Hypercuber constructor
HyperCube::HyperCube(int k, int w, int probes, int M, int N, int vectorSize){


	
	this->k = k;
	
	//Number of Buckets in Cube (number of possible binary codes)
	int cubeDimensions = 1<<k; //shift left (2^k)
	
	cout<<"Dimensions: "<<cubeDimensions<<endl;
	
	this->w = w;
	
	
	this->buckets = cubeDimensions;
	
	this->probes = probes; 
	
	this->N = N;
	
	this->M = M;
	
	//Create array of lists (create hypercube table)
	table = new list<ImageVector *>[this->buckets];
	
	//Array v 
	v = new double[vectorSize];
	
	//Array t
	t = new double[vectorSize];
	
	//Create F dictionary
	DictionaryF dict;
	
	//List with probes visited
	vector<int> probeList;
	
	//Store possible next probes(buckets) with min hamming distance
	vector<int> nextProbe;
	
	hammingDistanceCount = 0;
	
	
	//Seed v with Normal Distribution values
	NormalDistributionSeeder(&v, vectorSize);
	
	//Seed t with Uniform Distribution values
	UniformDistributionSeeder(&t, vectorSize, 0.0, this->w);
	
	cout<<"Object HyperCube was created"<<endl;
	cout<<endl;

}


//Array seeder with Normal Distribution values
void HyperCube::NormalDistributionSeeder(double** v, int vector_size){

	//cout<<"Entering Normal Dist"<<endl;
	
	//Initialize generator
	random_device rd;
	mt19937 gen(rd());
	
	double mean = 0.0;
	double standard_dev = 1.0;
	
	//Use of std::normal_distribution template
	normal_distribution<double> normalDist(mean, standard_dev);
	
	for (int i = 0; i < vector_size; ++i) {
		//Generate random normal dist values
        	double randomValue = normalDist(gen);
        	
        	//Seed array with values
		(*v)[i] = randomValue;
	}
	
	

}




//Array seeder with Uniform Distribution values
void HyperCube::UniformDistributionSeeder(double** t, int vector_size, double min,double max){

	//cout<<"Entering Uniform Dist"<<endl;
	
	//Initialize generator
	random_device rd;
	mt19937 gen(rd());
	
	
	//Use of std::uniform_real_distribution template
	uniform_real_distribution<double> distribution(min, max);
	
	for (int i = 0; i < vector_size; ++i) {
		//Generate random uniform dist values
        	double randomValue = distribution(gen);
        	
        	
        	//Seed array with values
		(*t)[i] = randomValue;
	}

}




//Calculate H 
int* HyperCube::calculateH(vector<unsigned char> *p, double* v, double* t, int w){

	int vector_size = 784;
	
	
	
	
	//Create H array of k functions
	int *h_functions = new int[this->k];
	
	
	//For each function in H (h_functions[])
	for (int i = 0; i < this->k; i++){

    		
    		//Calculate inner product of p*v
    		double innerProduct = 0.0; 
    		
    		

		for (int j = 0; j < vector_size; j++) {
   			innerProduct += (static_cast<double>((*p)[j])) * (v[j]);
   			
   			
		}
		
		
		//Calculate final h functions
    		h_functions[i] = abs((innerProduct + t[i]) / w); 
    		
    		
    		                                           
    	}
    	
    	
    		for(int i=0;i<2;i++){
    			//cout<<h_functions[i]<<endl;
    			
    		}
    	
    
    	
    	return h_functions;
}

int HyperCube::calculateF(int* h){

	
	
	//initialize empty binary code
	string binaryCode = "";
	
	
	//Build binary Code to determine bucket
	for(int i = 0; i< this->k; i++){
		int bit = this->dict.getValue(h[i]);
		//cout<<bit<<endl;// bits sometimes are same because h has same random values 
		binaryCode = binaryCode + to_string(bit);
	}
	
	
	int value = bitset<32>(binaryCode).to_ulong();
	
	delete[] h;
	
	return value;

}

int HyperCube::getIndex(ImageVector* key){

	int* h;
	
	

	h = calculateH(&(key->pixels), this->v, this->t, this->w);
	
	
	int index = calculateF(h);
	
	

	return index;

}


void HyperCube::InsertItem(ImageVector* key){

	//Get index
	int index = getIndex(key);
	
	//Store bucket that ImageVector was hashed in
	key->bucket.push_back(index);
	
	this->table[index].push_back(key);

}


//Get index of query, without inserting it 
void HyperCube::FakeInsert(ImageVector* key){

	//Get index
	int index = getIndex(key);
	
	//Store bucket that ImageVector was hashed in
	key->bucket.push_back(index);

}

int HyperCube::getProbe(ImageVector* query){

	
	int probe = -1;

	if(probeList.empty()){
		//First probe is bucket the vector has been hashed into
		probeList.push_back(query->bucket[0]);
		hammingDistanceCount++;
		probe =  query->bucket[0];
		 
		 	
	}
	else{
		if(nextProbe.size() == 0){

		 //Get next probe
		 for(int i=0; i<buckets; i++){
		 	if(i == query->bucket[0])
		 		continue;
		 			 			
		 	//Get bucket num to string
		 	bitset<32> binaryRepresentation(i); 
		 	string binaryString = binaryRepresentation.to_string();
		 	
		 	//cout<<"Binary: "<<binaryString<<endl;
		 	
		 	//Get query->bucket num to string
		 	bitset<32> binaryRepr(query->bucket[0]); 
		 	string binaryStringQ = binaryRepr.to_string();
		 	//cout<<"Binary Query: "<<binaryStringQ<<endl;
		 	
		 	//Find hamming distance
		 	int distance = calculateHammingDistance(binaryString, binaryStringQ);
		 		 			 	
		 	//Store min distance probes
		 	if(distance == hammingDistanceCount){
		 		
		 		//If probe is not in probeList, we insert it
		 		auto iteration = find(probeList.begin(), probeList.end(), i);
		 		if(iteration == probeList.end()){
		 			//Add to possible next probes

		 			nextProbe.push_back(i);
		 		}
		 	}
				
		 
		 }
		 	//Increase hamming distance counter
			hammingDistanceCount++;
		  }
		  
		  
		  if(nextProbe.size() != 0){   		
		 
		 //Pick probe with uniform distribution by generating random index
		 	
		random_device rd;
    		mt19937 gen(rd());
    		
    		if(nextProbe.size()!=0){
    		uniform_int_distribution<int> distribution(0, nextProbe.size() - 1);

    		    		
    		// Generate a random index
    		int randIndex = distribution(gen);

   		// Access the selected element
    		int selectedProbe = nextProbe[randIndex];

    		//Insert Selected Probe in probeList
    		probeList.push_back(selectedProbe);

    		probe = selectedProbe;
    		
    		nextProbe.erase(remove(nextProbe.begin(), nextProbe.end(), probe), nextProbe.end());
    		}
    		
    		else

    			probe = -1;
   
		
		}
				
		 
	}
	

	return probe;

}



void HyperCube::FindNeighbours(ImageVector* query){


		double distance = 0.0;	
	
		//probes checked counter
		int probeCount = 0;
		
		int queryBucket = -1;
		
		
		//Data points that have been checked counter
		int m = 0;
		
		while(1){
		
		
		if(m==M)
				break;
    		

		
		if(probes==probeCount || probeCount==buckets || probeCount==M)
			break;
			

		//Determine query Bucket
		queryBucket = getProbe(query);
		
		 if(queryBucket==-1)
		 	break;
		 

		
		//Iterate bucket
		cout<<"Iterating Bucket "<<queryBucket<<endl;
		for (ImageVector* data : table[queryBucket]) {
		
			//Measure Euclidean Distance
			
			distance = calculateEuclideanDistance(query, data);
			
			if (distance==0)
				continue;
			
			//cout<<"Inserting id: "<<data->id<<" with distance: "<<distance<<endl;
			//Store Distances
			query->addNeighbour(data->id, distance);
			
			
			
        		
    		}
			m++;
			
    		probeCount++;
    		
    		}
    		
    		
    	
		//Clear probeList
		probeList.clear();
		
		//Resetting hammingDistanceCounter
		hammingDistanceCount=0;
		
		//Clear nextProbe list
		nextProbe.clear();
}


vector<Neighbour> HyperCube::RangeSearch(ImageVector* v, double range, int N){
	
	cout<<endl;
	cout<<endl;
	cout<<endl;
	
	//cout<<"Entering Range Search for query "<<v->id<<endl;
	
	this->FindNeighbours(v);

	if (v->neighbours.empty()) {
        cout << "No neighbors found." << endl;
        return vector<Neighbour>();  // Return an empty vector
    }
	
	vector<Neighbour> RangeNeighbours;
	
	v->sortNeighbours();
	//cout<<endl;
	//cout<<endl;
	//v->printNeighbours(10);
	
	for (const Neighbour& neighbour : v->neighbours){
	
		if(neighbour.distance <= range)
			RangeNeighbours.push_back(neighbour);
	}
	
	// Use an unordered set to track unique IDs
	unordered_set<int> uniqueIDs;

	// Create a vector to store unique Neighbours
	vector<Neighbour> UniqueRangeNeighbours;

	for (const Neighbour& neighbour : RangeNeighbours) {
    	// Check if the ID is not already in the set
    	if (uniqueIDs.insert(neighbour.id).second) {
        	UniqueRangeNeighbours.push_back(neighbour);
    	}
	}


    // Ensure that the size is not more than N
    if (static_cast<int>(UniqueRangeNeighbours.size()) > N) {
        UniqueRangeNeighbours.resize(N);
    }

    // Print the unique Neighbours
    // for (const Neighbour& neighbour : UniqueRangeNeighbours) {
    //     cout << "Unique Neighbour ID: " << neighbour.id << ", Distance: " << neighbour.distance << endl;
    // }

    return UniqueRangeNeighbours;
    
}

vector<Neighbour> HyperCube::CubeSearch(ImageVector* v, int N){

	

	//cout<<"Entering LSH Hashing Search"<<endl;
	
	FindNeighbours(v);
	
	// Ensure that v->neighbours is properly initialized before use
    if (v->neighbours.empty()) {
        cout << "No neighbors found." << endl;
        return vector<Neighbour>();  // Return an empty vector
    }


	vector<Neighbour> NearestNeighbours;
	
	v->sortNeighbours();
	//v->printNeighbours(N);

	for (const Neighbour& neighbour : v->neighbours){
	
		NearestNeighbours.push_back(neighbour);
	}

	// Use an unordered set to track unique IDs
	unordered_set<int> uniqueIDs;

	// Create a vector to store unique Neighbours
	vector<Neighbour> UniqueNearestNeighbours;

	for (const Neighbour& neighbour : NearestNeighbours) {
    	// Check if the ID is not already in the set
    	if (uniqueIDs.insert(neighbour.id).second) {
        	UniqueNearestNeighbours.push_back(neighbour);
    	}
	}


    // Ensure that the size is not more than N
    if (static_cast<int>(UniqueNearestNeighbours.size()) > N) {
        UniqueNearestNeighbours.resize(N);
    }

    // Print the unique Neighbours
    // for (const Neighbour& neighbour : UniqueNearestNeighbours) {
    //     cout << "Unique Neighbour ID: " << neighbour.id << ", Distance: " << neighbour.distance << endl;
    // }

    return UniqueNearestNeighbours;


}


vector<Neighbour> HyperCube::BruteForce(ImageVector* v, int N){

	

	//cout<<"Entering LSH Hashing Search"<<endl;
	int tempM = this->M;
	this->M = this->probes;

	FindNeighbours(v);
	
	// Ensure that v->neighbours is properly initialized before use
    if (v->neighbours.empty()) {
        cout << "No neighbors found." << endl;
        return vector<Neighbour>();  // Return an empty vector
    }


	vector<Neighbour> NearestNeighbours;
	
	v->sortNeighbours();
	//v->printNeighbours(N);

	for (const Neighbour& neighbour : v->neighbours){
	
		NearestNeighbours.push_back(neighbour);
	}

	// Use an unordered set to track unique IDs
	unordered_set<int> uniqueIDs;

	// Create a vector to store unique Neighbours
	vector<Neighbour> UniqueNearestNeighbours;

	for (const Neighbour& neighbour : NearestNeighbours) {
    	// Check if the ID is not already in the set
    	if (uniqueIDs.insert(neighbour.id).second) {
        	UniqueNearestNeighbours.push_back(neighbour);
    	}
	}


    // Ensure that the size is not more than N
    if (static_cast<int>(UniqueNearestNeighbours.size()) > N) {
        UniqueNearestNeighbours.resize(N);
    }

    // Print the unique Neighbours
    // for (const Neighbour& neighbour : UniqueNearestNeighbours) {
    //     cout << "Unique Neighbour ID: " << neighbour.id << ", Distance: " << neighbour.distance << endl;
    // }

	this->M = tempM;
    return UniqueNearestNeighbours;


}



void HyperCube::printTable(){
	
	int count =0;
	cout<<endl;
	for (int i = 0; i < this->buckets; i++) {
		
        	cout << "Bucket " << i << ": ";
        	for (const ImageVector* value : table[i]) {
        		
        		for(int j=0; j<784;j++){
        		cout << int(value->pixels[j]) << " ";
        		count++;
        		if(count==28){
        			cout<<endl;
        			count=0;
        		}
        		
        		}
        	}
        	cout << endl;
        	cout<<endl;
    	}

}


HyperCube::~HyperCube(){
	delete[] table;
	delete[] v;
	delete[] t;
	

	cout<<"Object HyperCube was destructed"<<endl;
}



