#ifndef Neighbour_Headers
#define Neighbour_Headers
#include <list>
#include <vector>

#include "ImageVector.h"


using namespace std;

class ImageVector;

//Struct to store information about a neighbour
struct Neighbour{

	int id;
	double distance;
	ImageVector* img;
	
};

#endif
