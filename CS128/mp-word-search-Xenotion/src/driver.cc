#include <iostream>
#include <string>
#include <vector>

#include "WordSearchSolver.hpp"

int main() {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'h'},
                                        {'h', 'e', 'l', 'l', 'o'},
                                        {'c', 'a', 'l', 'o', 'm'},
                                        {'a', 'e', 't', 'a', 'l'},
                                        {'t', 'e', 't', 'o', 'o'}};
  WordSearchSolver wss(puzzle);
  std::cout << wss.FindWord("hello", CheckDirection::kHorizontal);
  std::cout << wss.FindWord("hello");
}