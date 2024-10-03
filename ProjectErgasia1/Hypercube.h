#ifndef HyperCube_Headers
#define HyperCube_Headers
#include <list>
#include <vector>

#include "ImageVector.h"
#include "DictionaryF.h"
//#include "Functions.h"

using namespace std;

class HyperCube{

private:
    
    	//Pointer to list of pointers to ImageVector objects
	list<ImageVector *> *table;
    
    	//int id;
	int buckets;
	
	//Number of dimensions
	int k;
	
	//Bucket width
	int w;
	
	//Number of probes for search
	int probes;
	
	//N nearest neighbors
	int N;
	
	//Number of data points to be checked
	int M;
	
	//Create F dictionary
	DictionaryF dict;
	
	//List with probes visited
	vector<int> probeList;
	
	//Store possible next probes(buckets) with min hamming distance
	vector<int> nextProbe;
	
	//Hamming Distance count
	int hammingDistanceCount;
	
	double* v;
	double* t;
    

public:
	// Constructor
	HyperCube(int, int, int, int, int, int);
	void NormalDistributionSeeder(double**, int);
	
	void UniformDistributionSeeder(double**, int, double, double);
	int*  calculateH(vector<unsigned char>*, double*, double*, int);
	int getIndex(ImageVector*);
	int calculateF(int*);
	void InsertItem(ImageVector*);
	void FakeInsert(ImageVector*);
	void FindNeighbours(ImageVector* );
	void printTable();
	int getProbe(ImageVector*);
	vector<Neighbour> RangeSearch(ImageVector*, double, int);
	vector<Neighbour> CubeSearch(ImageVector*, int);
	vector<Neighbour> BruteForce(ImageVector*, int);

	
	
	
	~HyperCube();
};

#endif
