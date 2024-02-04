#include "List.h"
#include "Hashmap.h"
#include "Utils.h"
#include "Keywords.h"

#include <vector>
#include <string>


// Testing Custom Hashmap with custom doubly Linked list 



// Test subject
extern std::vector<std::string> Keywords; // DEFINED IN Utils.h

// Hashmap size
int mapSize = Keywords.size() * 1.0; // increasing map size, increases performance! 


int main() 
{
	Hashmap<std::string> hashmap(mapSize); // Hashmap that stores strings (keywords)
 //   std::vector<std::string> operations = { "Insert", "Lookup", "Delete" }; // operations that we are testing

	//for (const std::string& operation : operations)
	//{
 //       double totalTime = MeasureTime([&hashmap, &operation]()
 //           {
 //               if (operation == "Insert")
 //               {
 //                   for (const std::string& keyword : Keywords)
 //                   {
 //                       hashmap.Insert(keyword);
 //                   }
 //               }
 //               else if (operation == "Lookup")
 //               {
 //                   for (const std::string& keyword : Keywords)
 //                   {
 //                       hashmap.Find(keyword);
 //                   }
 //               }
 //               else if (operation == "Delete")
 //               {
 //                   for (const std::string& keyword : Keywords)
 //                   {
 //                       hashmap.Delete(keyword);
 //                   }
 //               }
 //           });
 //       double averageTime = totalTime / Keywords.size();
 //       PrintDuration(averageTime, operation);      
	//}

	// Measuring AVG Insert time
    double totalInsertTime = MeasureTime([&hashmap]()
        {
            for (const std::string& keyword : Keywords)
            {
                hashmap.Insert(keyword);
            }
        });
    double avgInsertTime = totalInsertTime / Keywords.size();
    PrintDuration(avgInsertTime, "Insert");
	
    // Measuring AVG Lookup time
	double totalLookupTime = MeasureTime([&hashmap]()
        {
            for (const std::string& keyword : Keywords)
            {
                hashmap.Find(keyword);
            }
        });
	double avgLookupTime = totalLookupTime / Keywords.size();
    PrintDuration(avgLookupTime, "Lookup");
	
    // Measuring AVG Delete time 
    double totalDeleteTime = MeasureTime([&hashmap]()
        {
            for (const std::string& keyword : Keywords)
            {
                hashmap.Delete(keyword);
            }
        });
	double avgDeleteTime = totalDeleteTime / Keywords.size();
    PrintDuration(avgDeleteTime, "Delete");

    return 0;
}
