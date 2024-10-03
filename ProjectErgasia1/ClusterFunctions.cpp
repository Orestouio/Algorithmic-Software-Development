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


//Scale double values to fit in range [0,255]
vector<unsigned char> doublesToUnsignedChars(vector<double>& doublesVector) {
    vector<unsigned char> result;
    result.reserve(doublesVector.size());

    for (double value : doublesVector) {
        // Scale the double value to fit within the range [0, 255]
        double scaledValue = (value) * 255.0;
        
        
        // Round or truncate the scaled value to an integer
        int intValue = static_cast<int>(scaledValue);
        
        // Cast the integer to an unsigned char and store it in the result vector
        result.push_back(static_cast<unsigned char>(intValue));
    }

     cout<<"Result Vector:"<<endl;
	int coun =0;
	
			for(int p=0; p<784; p++){
				cout<<(int)result[p]<<" ";
				coun++;
				if(coun==28){
					cout<<endl;
					coun=0;
				}
			}
	

    return result;
}

//Binary Search
int binarySearch(double p[], int pSize, double x){

    int left = 0;
    int right = pSize - 1;

    while(left < right){

        int mid = left + (right-left)/2;

        if(p[mid] >= x){
            right = mid;
        }
        else{
            left = mid + 1;
        }

    }

    //cout<<"x is in ["<<p[left-1]<<","<<p[left]<<"]"<<endl;
    return left;

}


//Calculate Euclidean Distance
double calculateEuclideanDistance(ImageVector* query, ImageVector* dataImage) {
	
	double distance = 0.0;
    
	for (int i = 0; i < query->size; i++) {
		double diff = (query->pixels[i] )- (dataImage->pixels[i]);
		distance += diff * diff;
	}
	return sqrt(distance);
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



