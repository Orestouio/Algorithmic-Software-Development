#include <iostream>
#include <vector>
#include <algorithm>


#include "ImageVector.h"


using namespace std;




void ImageVector::addNeighbour(int id, double distance){
	
		(this->neighbours).push_back({id, distance});
	
}


void ImageVector::printNeighbours(int N){
	
	int count = 0;
	for (const Neighbour& neighbour : neighbours) {
		if(count==N)
			break;
		cout <<"Neighbour ID: " << neighbour.id << ", Distance: " << neighbour.distance << endl;
		count++;
}
	
}


bool compareDistance(const Neighbour& a, const Neighbour& b) {
	//compare based on distance
	return a.distance < b.distance;
}



void ImageVector::sortNeighbours(){

	
	//Sort vector of neighbours based on distance
	sort(neighbours.begin(), neighbours.end(), compareDistance);
	
	

}

void ImageVector::printImageVector(){

	int count = 0;

	for(int i=0; i< this->size; i++){
	
		cout <<int(pixels[i]) << " ";
        	count++;
        	if(count==28){
        		count = 0;
        		cout << endl;
        	}
        
	}


}
