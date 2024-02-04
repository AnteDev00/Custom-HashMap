#include "List.h"
#include "Hashmap.h"
#include "Keywords.h"

#include <vector>

// In this project I tested my Custom Hashmap approach 
// with my Custom Linked List class

// It was created for learning purposes
// and it is not highly polished


int main() {

    vector<List<string>*> HashMap(MAP_SIZE); // increasing map size, increases performance! 

	// Measuring AVG Insert time
    double avgInsertDuration = MeasureFunctionTime( FillHashMap, HashMap, Keywords);
	PrintDuration(avgInsertDuration, "Insert");

    // Measuring AVG Lookup time
	double avgLookupDuration = MeasureFunctionTime( LookUpAllElements, HashMap, Keywords);
	PrintDuration(avgLookupDuration, "Lookup");
    
    // Measuring AVG Delete time 
    double avgDeleteDuration = MeasureFunctionTime( DeleteHashMap, HashMap);
    PrintDuration(avgDeleteDuration, "Delete");
    

    // Printing amount of RESOLVED collisions
    PrintCollisionsStats(HashMap);

    // CleanUp 
	for (List<string>* list : HashMap)
		delete list;
}
