#pragma once
#include <iostream>
#include <chrono>

#include <iomanip> // std::setprecision

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
	std::cout << "\nAverage *" << _operation << "* time:\t " << durationInNanoSec << " Nanoseconds" << "\tor\t" << MilionOpPerSec << " Milion op/s\n";
}
