#pragma once
#include "Keywords.h"

#include <functional> // For std::forward

#include <iostream>
#include <chrono>


// This header file holds functions necessary to do the testing of the hash map



using namespace std; // I dont ususally use it, but for this project its pretty handy 

template <typename FuncType, typename... Args>
double MeasureFunctionTime(FuncType functionToMeasure, Args&&... args)
{
    auto start = std::chrono::high_resolution_clock::now();
    functionToMeasure(std::forward<Args>(args)...); // Forward arguments
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    return static_cast<double>(duration.count() / KEYWORD_SIZE);
}

inline int Hash(const string& _Keyword)
{
    return hash<string>{}(_Keyword) % MAP_SIZE;
}

// Insert
void FillHashMap(vector<List<string>*>& _HashMap, vector<string>& _Keywords)
{
    // Fill the vector with Keywords
    for (int i = 0; i < KEYWORD_SIZE; i++)
    {
        int hashIndex = Hash(Keywords[i]); // Calculate the hash
        if (_HashMap[hashIndex] == nullptr)  // If it's the first element with that hash, create a new linked list
        {
            _HashMap[hashIndex] = new List<string>();
            _HashMap[hashIndex]->AddBack(Keywords[i]);
        }
        else // if it's not first elem
        {
            _HashMap[hashIndex]->AddBack(Keywords[i]);
        }
    }
}

// Lookup
void LookUpAllElements(vector<List<string>*>& _HashMap, vector<string>& _Keywords)
{
    // Finds all elements by their hashes
    for (int i = 0; i < KEYWORD_SIZE; i++)
    {
        int hashIndex = Hash(Keywords[i]); // Calc the hash, truncate it to fit MAP_SIZE
        int listIndex = _HashMap[hashIndex]->FindIndex(Keywords[i]); // Find the INDEX of element
        string keyword = _HashMap[hashIndex]->NodeAt(listIndex); // Access the element
    }
}

// Delete
void DeleteHashMap(vector<List<string>*>& _HashMap)
{
    for (int i = 0; i < KEYWORD_SIZE; i++)
        if (_HashMap[i] != nullptr)
        {
            int listSize = _HashMap[i]->GetSize();

            for (int j = 0; j < listSize; j++)
                _HashMap[i]->DeleteBack();
        }
}

void PrintDuration(const double& _avgDuration, const std::string& _operation)
{
    const int nanosecInSec = 1'000'000'000;
    double MOperationsPerSec = (nanosecInSec / _avgDuration) / 1'000'000; 

    // Log to console
    cout << "\nAverage " << _operation << " time:\n" << "Best case scenario, " << _avgDuration << " nanoseconds, ";
    cout << "which is: " << MOperationsPerSec << " Milion Operations/s\n";
    cout << "\n------------------------------------------------------------\n";
}

void PrintCollisionsStats(vector<List<string>*>& _HashMap)
{
	int collisions = 0;
    
    // Calculating collisions
    for (int i = 0; i < MAP_SIZE; i++)
    {
        if (_HashMap[i] == nullptr
            || _HashMap[i]->IsEmpty())
        {
            continue;
        }
        else 
        {
            collisions = collisions + _HashMap[i]->GetSize() - 1;
        }
    }
    // Printing
    cout << "\nNumber of Resolved Collisions: " << collisions << "\n";
}


