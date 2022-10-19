// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }

TEST_CASE("Directions", "") {
  std::vector<std::vector<char>> puzzle = {
    {'l', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'},
    {'u', 'l', 'm', 'n', 'o', 'p', 't', 'r', 's', 't'},
    {'m', 'v', 't', 'e', 'a', 'm', 'a', 'e', 'c', 'd'},
    {'b', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'a', 'n'},
    {'e', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'm'},
    {'r', 'y', 'a', 'b', 'e', 'd', 'e', 't', 'g', 'h'},
    {'j', 'j', 'k', 'a', 'm', 'n', 'o', 'e', 'q', 'r'},
    {'a', 't', 'm', 'v', 'w', 'x', 'y', 'a', 'a', 'b'},
    {'c', 'd', 'e', 'f', 'g', 'h', 'i', 'm', 'k', 'l'},
    {'k', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'}};

  WordSearchSolver solver(puzzle);

  WordLocation word_location = solver.FindWord("team", CheckDirection::kHorizontal);
  REQUIRE(word_location.word == "team");
  REQUIRE(word_location.char_positions.size() == 4);
  REQUIRE(word_location.char_positions[0].character == 't');
  REQUIRE(word_location.char_positions[0].row == 2);
  REQUIRE(word_location.char_positions[0].col == 2);
  REQUIRE(word_location.char_positions[1].character == 'e');
  REQUIRE(word_location.char_positions[1].row == 2);
  REQUIRE(word_location.char_positions[1].col == 3);
  REQUIRE(word_location.char_positions[2].character == 'a');
  REQUIRE(word_location.char_positions[2].row == 2);
  REQUIRE(word_location.char_positions[2].col == 4);
  REQUIRE(word_location.char_positions[3].character == 'm');
  REQUIRE(word_location.char_positions[3].row == 2);
  REQUIRE(word_location.char_positions[3].col == 5);

  WordSearchSolver solver2(puzzle);

  WordLocation word_location2 = solver2.FindWord("team", CheckDirection::kVertical);
  REQUIRE(word_location2.word == "team");
  REQUIRE(word_location2.char_positions.size() == 4);
  REQUIRE(word_location2.char_positions[0].character == 't');
  REQUIRE(word_location2.char_positions[0].row == 5);
  REQUIRE(word_location2.char_positions[0].col == 7);
  REQUIRE(word_location2.char_positions[1].character == 'e');
  REQUIRE(word_location2.char_positions[1].row == 6);
  REQUIRE(word_location2.char_positions[1].col == 7);
  REQUIRE(word_location2.char_positions[2].character == 'a');
  REQUIRE(word_location2.char_positions[2].row == 7);
  REQUIRE(word_location2.char_positions[2].col == 7);
  REQUIRE(word_location2.char_positions[3].character == 'm');
  REQUIRE(word_location2.char_positions[3].row == 8);
  REQUIRE(word_location2.char_positions[3].col == 7);

  WordSearchSolver solver3(puzzle);

  WordLocation word_location3 = solver3.FindWord("team", CheckDirection::kLeftDiag);
  REQUIRE(word_location3.word == "team");
  REQUIRE(word_location3.char_positions.size() == 4);
  REQUIRE(word_location3.char_positions[0].character == 't');
  REQUIRE(word_location3.char_positions[0].row == 4);
  REQUIRE(word_location3.char_positions[0].col == 5);
  REQUIRE(word_location3.char_positions[1].character == 'e');
  REQUIRE(word_location3.char_positions[1].row == 5);
  REQUIRE(word_location3.char_positions[1].col == 4);
  REQUIRE(word_location3.char_positions[2].character == 'a');
  REQUIRE(word_location3.char_positions[2].row == 6);
  REQUIRE(word_location3.char_positions[2].col == 3);
  REQUIRE(word_location3.char_positions[3].character == 'm');
  REQUIRE(word_location3.char_positions[3].row == 7);
  REQUIRE(word_location3.char_positions[3].col == 2);

  WordSearchSolver solver4(puzzle);

  WordLocation word_location4 = solver4.FindWord("team", CheckDirection::kRightDiag);
  REQUIRE(word_location4.word == "team");
  REQUIRE(word_location4.char_positions.size() == 4);
  REQUIRE(word_location4.char_positions[0].character == 't');
  REQUIRE(word_location4.char_positions[0].row == 1);
  REQUIRE(word_location4.char_positions[0].col == 6);
  REQUIRE(word_location4.char_positions[1].character == 'e');
  REQUIRE(word_location4.char_positions[1].row == 2);
  REQUIRE(word_location4.char_positions[1].col == 7);
  REQUIRE(word_location4.char_positions[2].character == 'a');
  REQUIRE(word_location4.char_positions[2].row == 3);
  REQUIRE(word_location4.char_positions[2].col == 8);
  REQUIRE(word_location4.char_positions[3].character == 'm');
  REQUIRE(word_location4.char_positions[3].row == 4);
  REQUIRE(word_location4.char_positions[3].col == 9);

  WordLocation test = solver4.FindWord("yeet");
  REQUIRE(test.word.empty());
  REQUIRE(test.char_positions.empty());
  WordLocation test1 = solver4.FindWord("yeet", CheckDirection::kHorizontal);
  REQUIRE(test1.word.empty());
  REQUIRE(test1.char_positions.empty());
  WordLocation test2 = solver4.FindWord("yeet", CheckDirection::kVertical);
  REQUIRE(test2.word.empty());
  REQUIRE(test2.char_positions.empty());
  WordLocation test3 = solver4.FindWord("yeet", CheckDirection::kLeftDiag);
  REQUIRE(test3.word.empty());
  REQUIRE(test3.char_positions.empty());
  WordLocation test4 = solver4.FindWord("yeet", CheckDirection::kRightDiag);
  REQUIRE(test4.word.empty());
  REQUIRE(test4.char_positions.empty());

}
/////////////////////////////////////////////////////////////////////////////////////////////