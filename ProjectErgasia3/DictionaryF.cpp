#include <iostream>
#include <random>
#include <list>
#include <vector>
#include <algorithm>

#include "DictionaryF.h"



using namespace std;

int DictionaryF::getValue(int h){

	
	//If we find value in zero vector, return 0
	auto it = find(zero.begin(), zero.end(), h);
	if(it != zero.end()){
		return 0;
	}
	
	//If we find value in one vector, return 1
	it = find(one.begin(), one.end(), h);
	
	if(it != one.end()){
		return 1;
	}
	
	//Initialize generator
	random_device rd;
	mt19937 gen(rd());
	
	
	//Use of std::uniform_real_distribution template
	uniform_int_distribution<int> distribution(0, 1);
	
	
	double randomValue = distribution(gen);
        
        
        //Store new value mapping	
	if(randomValue==0)
		zero.push_back(h);
	else
		one.push_back(h);
		
	//return bit
	return randomValue;
			
		
	



}




