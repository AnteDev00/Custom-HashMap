#include "List.h"
#include "Hashmap.h"
#include "Utils.h"
#include "Keywords.h"

#include <vector>
#include <string>


// Testing Custom Hashmap with custom doubly Linked list 


// Test subject
extern std::vector<std::string> Keywords; // DEFINED IN "Keywords.h"

int main() 
{
    int mapSize = Keywords.size() * 1.0; // Hashmap size // increasing map size, increases performance! 
	Hashmap<std::string> hashmap(mapSize);  
    std::vector<std::string> operations = { "Insert", "Lookup", "Delete" }; // operations that we are testing

	for (const std::string& operation : operations)
	{
        double totalTime = MeasureTime([&hashmap, &operation]()
            {
                if (operation == "Insert")
                {
                    for (const std::string& keyword : Keywords)
                    {
                        hashmap.Insert(keyword);
                    }
                }
                else if (operation == "Lookup")
                {
                    for (const std::string& keyword : Keywords)
                    {
                        hashmap.Find(keyword);
                    }
                }
                else if (operation == "Delete")
                {
                    for (const std::string& keyword : Keywords)
                    {
                        hashmap.Delete(keyword);
                    }
                }
            });
        double averageTime = totalTime / Keywords.size();
        PrintDuration(averageTime, operation);      
	}
    return 0;
}
