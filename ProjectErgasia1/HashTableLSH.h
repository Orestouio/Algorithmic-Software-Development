#ifndef HashTableLSH_Headers
#define HashTableLSH_Headers
#include <list>
#include <vector>

#include "ImageVector.h"
//#include "Functions.h"

using namespace std;

class Hash_Table_LSH{

private:
    
    	//Pointer to list of pointers to ImageVector objects
	list<ImageVector *> *table;
    
    	//int id;
	int buckets;
	
	//Number of h functions
	int k;
	
	//Bucket width
	int w;
	
	
	double* v;
	double* t;
    

public:
	// Constructor
	Hash_Table_LSH(int, int, int, int);
	
	void InsertItem(ImageVector*);
	
	void FakeInsert(ImageVector *);
	
	void FindNeighbours(ImageVector*);
	
	vector<Neighbour> RangeSearch(ImageVector*, double, int);
	
	void printTable();
	
	void NormalDistributionSeeder(double**, int);
	
	void UniformDistributionSeeder(double**, int, double, double);
	int * calculateH(vector<unsigned char>*, double*, double*, int);
	
	int AmplifiedHashFunctionG(ImageVector*);

	vector<Neighbour> LSHnn(ImageVector*, int);
	
	
	
	
	~Hash_Table_LSH();
};

#endif
