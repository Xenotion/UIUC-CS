#include <iostream>

#include "functions.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./bin/exec word" << std::endl;
    return 1;
  }

  std::string word = argv[1];
  std::cout << Solve(word) << std::endl;
  
  return 0;
}