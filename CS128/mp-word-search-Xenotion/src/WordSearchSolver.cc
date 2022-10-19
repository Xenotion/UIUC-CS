#include "WordSearchSolver.hpp"

WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle) {
  puzzle_ = puzzle;
  puzzle_height_ = puzzle.size();
  puzzle_width_ = puzzle.at(0).size();
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  if (WordSearchSolver::FindWord(word, CheckDirection::kHorizontal).word ==
      word) {
    return WordSearchSolver::FindWord(word, CheckDirection::kHorizontal);
  }

  if (WordSearchSolver::FindWord(word, CheckDirection::kVertical).word ==
      word) {
    return WordSearchSolver::FindWord(word, CheckDirection::kVertical);
  }

  if (WordSearchSolver::FindWord(word, CheckDirection::kLeftDiag).word ==
      word) {
    return WordSearchSolver::FindWord(word, CheckDirection::kLeftDiag);
  }

  if (WordSearchSolver::FindWord(word, CheckDirection::kRightDiag).word ==
      word) {
    return WordSearchSolver::FindWord(word, CheckDirection::kRightDiag);
  }

  return WordLocation{};
}

WordLocation WordSearchSolver::HorizontalSearch(const std::string& word,
                                                WordLocation& fword,
                                                CharPositions& c) {
  for (int i = 0; i < static_cast<int>(puzzle_height_); i++) {
    for (int j = 0; j < static_cast<int>(puzzle_width_ - word.length() + 1);
         j++) {
      std::string temp;

      for (int k = 0; k < static_cast<int>(word.length()); k++) {
        temp += puzzle_.at(i).at(j + k);
      }

      if (temp == word) {
        fword.word = temp;

        for (int l = 0; l < static_cast<int>(temp.length()); l++) {
          c.character = word.at(l);
          c.row = i;
          c.col = j + l;

          fword.char_positions.push_back(c);
        }
        return fword;
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::VerticalSearch(const std::string& word,
                                              WordLocation& fword,
                                              CharPositions& c) {
  for (int i = 0; i < static_cast<int>(puzzle_height_ - word.length() + 1);
       i++) {
    for (int j = 0; j < static_cast<int>(puzzle_width_); j++) {
      std::string temp;

      for (int k = 0; k < static_cast<int>(word.length()); k++) {
        temp += puzzle_.at(i + k).at(j);
      }

      if (temp == word) {
        fword.word = temp;

        for (int l = 0; l < static_cast<int>(temp.length()); l++) {
          c.character = word.at(l);
          c.row = i + l;
          c.col = j;

          fword.char_positions.push_back(c);
        }
        return fword;
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::LeftdiagSearch(const std::string& word,
                                              WordLocation& fword,
                                              CharPositions& c) {
  for (int i = 0; i < static_cast<int>(puzzle_height_ - word.length() + 1);
       i++) {
    for (int j = static_cast<int>(puzzle_width_ - 1);
         j > static_cast<int>(word.length() - 2);
         j--) {
      std::string temp;

      for (int k = 0; k < static_cast<int>(word.length()); k++) {
        temp += puzzle_.at(i + k).at(j - k);
      }

      if (temp == word) {
        fword.word = temp;

        for (int l = 0; l < static_cast<int>(temp.length()); l++) {
          c.character = word.at(l);
          c.row = i + l;
          c.col = j - l;

          fword.char_positions.push_back(c);
        }
        return fword;
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::RightdiagSearch(const std::string& word,
                                               WordLocation& fword,
                                               CharPositions& c) {
  for (int i = 0; i < static_cast<int>(puzzle_height_ - word.length() + 1);
       i++) {
    for (int j = 0; j < static_cast<int>(puzzle_width_ - word.length() + 1);
         j++) {
      std::string temp;

      for (int k = 0; k < static_cast<int>(word.length()); k++) {
        temp += puzzle_.at(i + k).at(j + k);
      }

      if (temp == word) {
        fword.word = temp;

        for (int l = 0; l < static_cast<int>(temp.length()); l++) {
          c.character = word.at(l);
          c.row = i + l;
          c.col = j + l;

          fword.char_positions.push_back(c);
        }
        return fword;
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  WordLocation fword{};
  CharPositions c{};

  if (direction == CheckDirection::kHorizontal) {
    return WordSearchSolver::HorizontalSearch(word, fword, c);
  }

  if (direction == CheckDirection::kVertical) {
    return WordSearchSolver::VerticalSearch(word, fword, c);
  }

  if (direction == CheckDirection::kLeftDiag) {
    return WordSearchSolver::LeftdiagSearch(word, fword, c);
  }

  if (direction == CheckDirection::kRightDiag) {
    return WordSearchSolver::RightdiagSearch(word, fword, c);
  }

  return WordLocation{};
}

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}
