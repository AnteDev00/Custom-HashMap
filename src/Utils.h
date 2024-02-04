#pragma once
#include <iostream>
#include <chrono>


template <typename Func>
double MeasureTime(Func _Func) 
{
	auto start = std::chrono::high_resolution_clock::now();
	_Func();
	auto end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration<double>(end - start).count();  // Returns duration in seconds
}

void PrintDuration(const double& _avgDurInSec, const std::string& _operation)
{
	double durationInNanoSec = _avgDurInSec * 1'000'000'000;

	double operationsPerSec = 1.0 / _avgDurInSec;
	double MilionOpPerSec = operationsPerSec / 1'000'000.0;

	// Log to console
	std::cout << "\nAverage " << _operation << " time:\n";
	std::cout << durationInNanoSec << " nanoseconds.  (or: " << _avgDurInSec << " seconds)\n"
			  << MilionOpPerSec << " milion operations/sec.  (or: " << operationsPerSec << " operations/sec)";
	std::cout << "\n------------------------------------------------------------\n";
}
