#ifndef ImageVector_Headers
#define ImageVector_Headers

#include <vector>

#include "Neighbour.h"

using namespace std;

class ImageVector{

public:

	//vector to store pixels
    	vector<unsigned char> pixels;
    
	int size = pixels.size();
    	int id;
    	
    	//Save bucket num from each table the object is stored
    	
    	vector<int> bucket; //bucket should be an array!!!!!!!!!
    	//int bucket;
    	
    	//vector of neighbours to store info on datapoints in the same bucket
    	vector<Neighbour> neighbours;
    
    
    	//Constructor
     	ImageVector(int numPixels, int id) : pixels(numPixels),id(id) {
     	
			
	}
    
    	bool compareType(const ImageVector&, const ImageVector&);
    	void addNeighbour(int, double);
    	void sortNeighbours();
    	void printNeighbours(int);
    	void printImageVector();
};


#endif
