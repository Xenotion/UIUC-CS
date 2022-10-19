#ifndef WORDSEARCHSOLVER_HPP
#define WORDSEARCHSOLVER_HPP

#include <cstddef>
#include <string>
#include <vector>
#include <iostream>

#include "WordLocation.hpp"

enum class CheckDirection { kHorizontal, kVertical, kLeftDiag, kRightDiag };

class WordSearchSolver {
public:
  WordSearchSolver(const std::vector<std::vector<char>>& puzzle);
  WordLocation FindWord(const std::string& word);
  WordLocation FindWord(const std::string& word, CheckDirection direction);
  WordLocation HorizontalSearch(const std::string& word, WordLocation& fword, CharPositions& c);
  WordLocation VerticalSearch(const std::string& word, WordLocation& fword, CharPositions& c);
  WordLocation LeftdiagSearch(const std::string& word, WordLocation& fword, CharPositions& c);
  WordLocation RightdiagSearch(const std::string& word, WordLocation& fword, CharPositions& c);

private:
  bool LocationInBounds(size_t row, size_t col) const;
  std::vector<std::vector<char>> puzzle_;
  size_t puzzle_height_;
  size_t puzzle_width_;
};

#endif