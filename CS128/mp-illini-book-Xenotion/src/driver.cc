#include <iostream>

#include "illini_book.hpp"

int main() {
  IlliniBook illini_book("example/persons.csv", "example/relations.csv");
  // illini_book.PrintGraph();

  // get steps from 1 to 2 
  std::vector<int> steps = illini_book.GetSteps(1, 2);
  std::cout << "Steps from 1 to 1: ";
  for (auto step : steps) {
    std::cout << step << " ";
  }
  std::cout << std::endl;

  return 0;
}
