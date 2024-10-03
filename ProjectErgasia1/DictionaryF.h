#ifndef DictionaryF_Headers
#define DictionaryF_Headers
#include <list>
#include <vector>




using namespace std;

class DictionaryF{

private:

	//Stores values that map to zero
	vector<int> zero;
	
	//Stores values that map to one
	vector <int> one;
    
    	

public:
	int getValue(int);
	
	
	
};

#endif
