#pragma once
#include "List.h"

#include <functional> // For std::fucntion
#include <vector>


// Header-only, templated Hashmap class, with a custom Doubly Linked list implementation, also not thread-safe
// Supports: Insert, Find, Delete and GetMapSize, GetKeySize, GetCollisions

template<typename type>
class Hashmap
{
public:
	Hashmap(int _MapSize) {
		if (_MapSize <= 0) 
        {
			throw std::out_of_range("Invalid map size");
		}
		m_Hashmap.resize(_MapSize); // Sets size and capacity, and null-initializes all elements
		m_MapSize = _MapSize;
		m_KeySize = 0;
		m_Collisions = 0;
	}
	~Hashmap() 
    { 
	    for(List<type>* list : m_Hashmap)
	    {
		    delete list;
	    }
    } 
public:
	void Insert(const type& _Keyword) 
    {
		int listIndex = Hash(_Keyword); // find index
		if (m_Hashmap[listIndex] == nullptr) // if its the first element
		{
            m_Hashmap[listIndex] = new List<type>(); // create a new list
			m_Hashmap[listIndex]->AddBack(_Keyword); // add to the list
		}
		else // collision happened
		{
			m_Hashmap[listIndex]->AddBack(_Keyword); // add to an existing list
			m_Collisions++; // increase collisions
		}
    }
    type& Find(const type& _Keyword)
    {
		// find list index
        int listIndex = Hash(_Keyword); 
		if (m_Hashmap[listIndex] == nullptr)
			throw std::out_of_range("Keyword not found");
		else
		{
			return m_Hashmap[listIndex]->Find(_Keyword);
		}
        
    }
    void Delete(const type& _Keyword)
    {
		// find list index
        int listIndex = Hash(_Keyword); 
		
		// check if list is empty
		if (m_Hashmap[listIndex] == nullptr)
			throw std::out_of_range("Keyword not found");
		else
		{
			// delete element
			m_Hashmap[listIndex]->Delete(_Keyword); 
		}
    }
public:
	void GetCollisions() const { return m_Collisions; }
	void GetMapSize() const { return m_MapSize; }
	void GetKeySize() const { return m_KeySize; }
private:
	std::vector<List<type>*> m_Hashmap; // actual hashmap
    int m_MapSize; // size of the map
	int m_KeySize; // number of elements in the map
	int m_Collisions; // number of elements with same hash
private:
	inline int Hash(const type& _Keyword) const { return std::hash<type>{}(_Keyword) % m_MapSize; }
};
