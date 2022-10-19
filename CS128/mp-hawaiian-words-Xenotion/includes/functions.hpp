#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <vector>

// Your function declarations should go in this header file.
int CheckStr(std::string& s);
std::string ConvStr(char c);
int CheckVow(char s);
int CheckCons(char s);
void Helper(const std::string& word, std::string& s, unsigned int& i);
std::string Solve(std::string word);

#endif