#include "List.h"
#include "Hashmap.h"
#include "Utils.h"
#include "Keywords.h"

#include <vector>
#include <string>


// ------------------- Testing Hashmap Performance ---------------------


// Test subject
extern std::vector<std::string> Keywords; // DEFINED IN "Keywords.h"


int main() 
{
    int hashmapSize = Keywords.size() * 1.45; // increasing map size, increases performance! 
	Hashmap<std::string> hashmap(hashmapSize);
    std::vector<std::string> operations = { "Insert", "Lookup", "Delete" }; // operations that we are testing

	// Testing each operation
	for (const std::string& operation : operations)
	{
        double totalTime = MeasureTime([&hashmap, &operation]()
            {
                // testing Insert operation
		if (operation == "Insert") 
                {
                    for (const std::string& keyword : Keywords)
                    {
                        hashmap.Insert(keyword);
                    }
                }
                // testing Lookup operation
		else if (operation == "Lookup") 
                {
                    for (const std::string& keyword : Keywords)
                    {
                        hashmap.Find(keyword);
                    }
                }
				// testing Delete operation
                else if (operation == "Delete")
                {
                    for (const std::string& keyword : Keywords)
                    {
                        hashmap.Delete(keyword);
                    }
                }
            });
		
        // calculate average time
        double averageTime = totalTime / Keywords.size();

		// print average time
        PrintDuration(averageTime, operation); 
	}

    std::cout << "\n----------------------------\n\n";
    return 0;
}
