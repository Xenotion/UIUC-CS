#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "utilities.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int MostFreq(std::string& str, std::string& sequence);
int Helper(std::string& file, std::string& sequence);
void HelperTwo(std::string& sequence, std::string& line, std::string& s, std::vector<std::string>& lookup2, std::vector<int>& lookup3);

#endif