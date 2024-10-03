#include <iostream>
#include <random>
#include <list>
#include <vector>
#include <numeric>
#include <unordered_set>

#include "HashTableLSH.h"
#include "ImageVector.h"
#include "Functions.h"

using namespace std;

// Hash_Table_LSH constructor
Hash_Table_LSH::Hash_Table_LSH(int buckets, int k, int w, int vectorSize)
{

	this->buckets = buckets;
	this->k = k;
	this->w = w;

	// Create array of lists
	table = new list<ImageVector *>[this->buckets];

	// Array v
	v = new double[vectorSize];

	// Array t
	t = new double[vectorSize];

	// Seed v with Normal Distribution values
	NormalDistributionSeeder(&v, vectorSize);

	// Seed t with Uniform Distribution values
	UniformDistributionSeeder(&t, vectorSize, 0.0, this->w);

	// cout<<"Object Hash Table LSH was created"<<endl;
}

// Array seeder with Normal Distribution values
void Hash_Table_LSH::NormalDistributionSeeder(double **v, int vector_size)
{

	// cout<<"Entering Normal Dist"<<endl;

	// Initialize generator
	random_device rd;
	mt19937 gen(rd());

	double mean = 0.0;
	double standard_dev = 1.0;

	// Use of std::normal_distribution template
	normal_distribution<double> normalDist(mean, standard_dev);

	for (int i = 0; i < vector_size; ++i)
	{
		// Generate random normal dist values
		double randomValue = normalDist(gen);

		// Seed array with values
		(*v)[i] = randomValue;
	}
}

// Array seeder with Uniform Distribution values
void Hash_Table_LSH::UniformDistributionSeeder(double **t, int vector_size, double min, double max)
{

	// cout<<"Entering Uniform Dist"<<endl;

	// Initialize generator
	random_device rd;
	mt19937 gen(rd());

	// Use of std::uniform_real_distribution template
	uniform_real_distribution<double> distribution(min, max);

	for (int i = 0; i < vector_size; ++i)
	{
		// Generate random uniform dist values
		double randomValue = distribution(gen);

		// Seed array with values
		(*t)[i] = randomValue;
	}
}

// Calculate H
int *Hash_Table_LSH::calculateH(vector<unsigned char> *p, double *v, double *t, int w)
{

	int vector_size = 784;

	// Create H array of k functions
	int *h_functions = new int[this->k];

	// For each function in H (h_functions[])
	for (int i = 0; i < k; i++)
	{

		// Calculate inner product of p*v
		double innerProduct = 0.0;

		for (int j = 0; j < vector_size; j++)
		{
			innerProduct += (static_cast<double>((*p)[j])) * (v[j]);
		}
		// double innerProduct = inner_product(p, p + vector_size, v, 0);

		// Calculate final h function
		h_functions[i] = abs((innerProduct + t[i]) / w);

		// cout<<innerProduct<<endl;
	}

	return h_functions;
}

int Hash_Table_LSH::AmplifiedHashFunctionG(ImageVector *key)
{

	int *h;
	int g = 0;

	int vector_size = 784;

	// Create array r with uniform dist random values
	double *r = new double[vector_size];
	UniformDistributionSeeder(&r, vector_size, 1.0, 100.0);

	// Calculate h functions
	h = calculateH(&(key->pixels), this->v, this->t, this->w);

	// print h[i] for debugging
	for (int i = 0; i < this->k; i++)
	{
		// cout<<(h[i])<<endl;
	}

	// Calculate g function
	for (int i = 0; i < this->k; i++)
	{

		g += r[i] + h[i];
	}

	// Final g mod number of buckets, to get index
	g = g % (this->buckets);

	// cout<<g<<endl;

	delete[] r;
	delete[] h;

	return g;
}

void Hash_Table_LSH::InsertItem(ImageVector *key)
{

	// Calculate index with Aplified Hash Function
	int index = AmplifiedHashFunctionG(key);

	// Update bucket the key is stored
	key->bucket.push_back(index);
	// key->bucket = index;

	// Insert key to Hash Table
	this->table[index].push_back(key);
}

// Get index of query, without inserting it
void Hash_Table_LSH::FakeInsert(ImageVector *key)
{

	// Get index
	int index = AmplifiedHashFunctionG(key);

	// Store bucket that ImageVector was hashed in
	key->bucket.push_back(index);
}

void Hash_Table_LSH::FindNeighbours(ImageVector *query)
{

	double distance = 0.0;
	int vectorSize = query->bucket.size();

	for (int i = 0; i < vectorSize; i++)
	{

		// Determine query Bucket
		int queryBucket = query->bucket[i];

		// Iterate bucket
		// cout<<"Iterating Bucket "<<queryBucket<<endl;
		for (ImageVector *data : table[queryBucket])
		{

			// Measure Euclidean Distance

			distance = calculateEuclideanDistance(query, data, 2);

			if (distance == 0)
				continue;

			// cout<<"Inserting id: "<<data->id<<" with distance: "<<distance<<endl;
			// Store Distances
			query->addNeighbour(data->id, distance);
		}
	}
}

vector<Neighbour> Hash_Table_LSH::LSHnn(ImageVector *v, int N)
{

	cout << "Entering LSH Hashing Search" << endl;

	FindNeighbours(v);

	// Ensure that v->neighbours is properly initialized before use
	if (v->neighbours.empty())
	{
		cout << "No neighbors found." << endl;
		return vector<Neighbour>(); // Return an empty vector
	}

	vector<Neighbour> NearestNeighbours;

	v->sortNeighbours();
	// v->printNeighbours(N);

	for (const Neighbour &neighbour : v->neighbours)
	{

		NearestNeighbours.push_back(neighbour);
	}

	// Use an unordered set to track unique IDs
	unordered_set<int> uniqueIDs;

	// Create a vector to store unique Neighbours
	vector<Neighbour> UniqueNearestNeighbours;

	for (const Neighbour &neighbour : NearestNeighbours)
	{
		// Check if the ID is not already in the set
		if (uniqueIDs.insert(neighbour.id).second)
		{
			UniqueNearestNeighbours.push_back(neighbour);
		}
	}

	// Ensure that the size is not more than N
	if (static_cast<int>(UniqueNearestNeighbours.size()) > N)
	{
		UniqueNearestNeighbours.resize(N);
	}

	// Print the unique Neighbours
	// for (const Neighbour& neighbour : UniqueNearestNeighbours) {
	//     cout << "Unique Neighbour ID: " << neighbour.id << ", Distance: " << neighbour.distance << endl;
	// }

	return UniqueNearestNeighbours;
}

vector<Neighbour> Hash_Table_LSH::RangeSearch(ImageVector *v, double range, int N)
{

	// cout<<"Entering Range Search"<<endl;

	FindNeighbours(v);

	// Ensure that v->neighbours is properly initialized before use
	if (v->neighbours.empty())
	{
		cout << "No neighbors found." << endl;
		return vector<Neighbour>(); // Return an empty vector
	}

	vector<Neighbour> RangeNeighbours;

	v->sortNeighbours();
	// v->printNeighbours(N);

	for (const Neighbour &neighbour : v->neighbours)
	{

		if (neighbour.distance <= range)
			RangeNeighbours.push_back(neighbour);
	}

	// Use an unordered set to track unique IDs
	unordered_set<int> uniqueIDs;

	// Create a vector to store unique Neighbours
	vector<Neighbour> UniqueRangeNeighbours;

	for (const Neighbour &neighbour : RangeNeighbours)
	{
		// Check if the ID is not already in the set
		if (uniqueIDs.insert(neighbour.id).second)
		{
			UniqueRangeNeighbours.push_back(neighbour);
		}
	}

	// Ensure that the size is not more than N
	if (static_cast<int>(UniqueRangeNeighbours.size()) > N)
	{
		UniqueRangeNeighbours.resize(N);
	}

	// Print the unique Neighbours
	// for (const Neighbour& neighbour : UniqueRangeNeighbours) {
	//     cout << "Unique Neighbour ID: " << neighbour.id << ", Distance: " << neighbour.distance << endl;
	// }

	return UniqueRangeNeighbours;
}

void Hash_Table_LSH::printTable()
{

	int count = 0;
	cout << endl;
	for (int i = 0; i < this->buckets; i++)
	{

		cout << "Bucket " << i << ": ";
		for (const ImageVector *value : table[i])
		{

			for (int j = 0; j < 784; j++)
			{
				cout << int(value->pixels[j]) << " ";
				count++;
				if (count == 28)
				{
					cout << endl;
					count = 0;
				}
			}
		}
		cout << endl;
		cout << endl;
	}
}

// Destructor
Hash_Table_LSH::~Hash_Table_LSH()
{

	delete[] table;
	delete[] v;
	delete[] t;

	// cout<<"Object Hash Table LSH was deleted"<<endl;
}
