#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
#include <list>
#include <cmath> 


#include "Functions.h"
#include "ImageVector.h"

using namespace std;

int magic_number, num_images, num_rows, num_cols;
int magic_numberQ, num_imagesQ, num_rowsQ, num_colsQ;






Hash_Table_LSH** CreateHashTables(int numberOfHashTables, int K){

	Hash_Table_LSH **Hash_Tables_Array = new Hash_Table_LSH *[numberOfHashTables];
	for (int i = 0; i < numberOfHashTables; i++)
	{
		//Create Hash Tables
		Hash_Tables_Array[i] = new Hash_Table_LSH(5,K,5,784);
    	}
    	    

	return Hash_Tables_Array;

}


//Calculate Euclidean Distance
double calculateEuclideanDistance(ImageVector* query, ImageVector* dataImage, int n) {
	
	double distance = 0.0;
    
	for (int i = 0; i < query->size; i++) {
		double diff = (query->pixels[i] )- (dataImage->pixels[i]);
		distance += pow(diff, n);
	}
	return pow(distance, 1.0 / n);
}

// Function to find the nearest neighbors within a specified range
vector<NeighbourBrute> FindNearestNeighborsBruteForce(ImageVector* query, vector<ImageVector>& dataset, double R, int items) {
    vector<NeighbourBrute> nearestNeighbors;
    cout << "We have items: " << items << " , we also have R = " << R << endl;
    int count =0;
    for (ImageVector& data : dataset) {
        
        double distance = calculateEuclideanDistance(query, &data, 2);

        if (distance <= R) {
            nearestNeighbors.emplace_back(data.id, distance);
           //cout << "We found id:" << data.id << " we find at distance: " << distance << endl;
        }
        count++;
    }

    // Sort the Neighbour vector by distance
    sort(nearestNeighbors.begin(), nearestNeighbors.end());

    // Resize the vector to contain at most 'items' neighbors
    if (nearestNeighbors.size() > static_cast<std::vector<NeighbourBrute>::size_type>(items)) {
        nearestNeighbors.resize(items);
    }

    return nearestNeighbors;
}

vector<NeighbourBrute> BruteForce(ImageVector * queries, vector<ImageVector>& dataset, double R, int items){
    
    vector<NeighbourBrute> nearestNeighbors1 , nearestNeighbors2;
    	nearestNeighbors1 = FindNearestNeighborsBruteForce(queries, dataset, R, items); // Pass the query by pointer, dataset, R value
        if(nearestNeighbors2.empty()){
            swap(nearestNeighbors1, nearestNeighbors2); 
        }else{
            nearestNeighbors2.insert(nearestNeighbors2.end(), nearestNeighbors1.begin(), nearestNeighbors1.end());
            // Sort the Neighbour vector by distance
            sort(nearestNeighbors2.begin(), nearestNeighbors2.end());

            // Resize the vector to contain at most 'items' neighbors
            if (nearestNeighbors2.size() > static_cast<std::vector<NeighbourBrute>::size_type>(items)) {
                nearestNeighbors2.resize(items);
            }
        }
    return nearestNeighbors2;
}


//  Read data from binary file function
vector<ImageVector> readImages(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        exit(1);
    }


    // Vector to hold vector<Image> objects	    
    vector<ImageVector> images;
    
    
    // Read the header information
    file.read((char*)(&magic_number), sizeof(magic_number));
    file.read((char*)(&num_images), sizeof(num_images));
    file.read((char*)(&num_rows), sizeof(num_rows));
    file.read((char*)(&num_cols), sizeof(num_cols));


   // Convert to little endian
    magic_number = __builtin_bswap32(magic_number);
    num_images = __builtin_bswap32(num_images);
    num_rows = __builtin_bswap32(num_rows);
    num_cols = __builtin_bswap32(num_cols);
    
    

    for (int i = 0; i < num_images; ++i) {
        ImageVector image(num_rows*num_cols,i);
      

        
        // Read the pixel data
        file.read((char*)(image.pixels.data()), num_rows * num_cols);

        images.push_back(image);
    }

    file.close();
    return images;
}





//  Read data from query binary file 
vector<ImageVector> readQuery(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        exit(1);
    }


    // Vector to hold vector<Image> objects	    
    vector<ImageVector> images;
    
    
    // Read the header information
    file.read((char*)(&magic_numberQ), sizeof(magic_numberQ));
    file.read((char*)(&num_imagesQ), sizeof(num_imagesQ));
    file.read((char*)(&num_rowsQ), sizeof(num_rowsQ));
    file.read((char*)(&num_colsQ), sizeof(num_colsQ));


   // Convert to little endian
    magic_numberQ = __builtin_bswap32(magic_numberQ);
    num_imagesQ = __builtin_bswap32(num_imagesQ);
    num_rowsQ = __builtin_bswap32(num_rowsQ);
    num_colsQ = __builtin_bswap32(num_colsQ);
    
    

    for (int i = 0; i < num_images; ++i) {
        ImageVector image(num_rows*num_cols,i);
      

        
        // Read the pixel data
        file.read((char*)(image.pixels.data()), num_rows * num_cols);

        images.push_back(image);
    }

    file.close();
   // cout<<"Number of test images "<<num_imagesQ<<endl;
    return images;
}



