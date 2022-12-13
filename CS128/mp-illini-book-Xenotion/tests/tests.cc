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
#include <catch/catch.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "illini_book.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Are Related", "") {
  IlliniBook illini_book("example/persons.csv", "example/relations.csv");
  REQUIRE(illini_book.AreRelated(1, 2) == true);
  REQUIRE(illini_book.AreRelated(3, 2) == true);
  REQUIRE(illini_book.AreRelated(1, 9) == false);
}

TEST_CASE("Are Related With Relationship", "") {
  IlliniBook illini_book("example/persons.csv", "example/relations.csv");
  REQUIRE(illini_book.AreRelated(1, 2, "128") == true);
  REQUIRE(illini_book.AreRelated(1, 2, "124") == false);
  REQUIRE(illini_book.AreRelated(1, 6, "128") == true);
  REQUIRE(illini_book.AreRelated(1, 6, "124") == true);
}

TEST_CASE("Get Related", "") {
  IlliniBook illini_book("example/persons.csv", "example/relations.csv");
  REQUIRE(illini_book.GetRelated(1, 2) == 1);
  REQUIRE(illini_book.GetRelated(3, 2) == 2);
  REQUIRE(illini_book.GetRelated(1, 9) == -1);
  REQUIRE(illini_book.GetRelated(1, 6) == 1);
}

TEST_CASE("Get Related With Relationship", "") {
  IlliniBook illini_book("example/persons.csv", "example/relations.csv");
  REQUIRE(illini_book.GetRelated(1, 2, "128") == 1);
  REQUIRE(illini_book.GetRelated(1, 2, "124") == -1);
  REQUIRE(illini_book.GetRelated(1, 6, "128") == 2);
  REQUIRE(illini_book.GetRelated(1, 6, "124") == 1);
}

TEST_CASE("Get Steps", "") {
  IlliniBook illini_book("example/persons.csv", "example/relations.csv");
  // initialise a vector
  std::vector<int> steps = {2, 3, 6};
  std::vector<int> steps2 = {7, 8};
  REQUIRE(illini_book.GetSteps(1, 1) == steps);
  REQUIRE(illini_book.GetSteps(1, 2) == steps2);
  REQUIRE(illini_book.GetSteps(1, 3).empty() == true);
  REQUIRE(illini_book.GetSteps(9, 1).empty() == true);
}

TEST_CASE("Count Groups", "") {
  IlliniBook illini_book("example/persons.csv", "example/relations.csv");
  REQUIRE(illini_book.CountGroups() == 3);
}

TEST_CASE("Count Groups With Relationship", "") {
  IlliniBook illini_book("example/persons.csv", "example/relations.csv");
  REQUIRE(illini_book.CountGroups("128") == 6);
  REQUIRE(illini_book.CountGroups("124") == 6);
  REQUIRE(illini_book.CountGroups("173") == 10);
}

TEST_CASE("Count Groups With Vector", "") {
  IlliniBook illini_book("example/persons.csv", "example/relations.csv");
  REQUIRE(illini_book.CountGroups(std::vector<std::string>{"128", "173"}) == 6);
  REQUIRE(illini_book.CountGroups(
              std::vector<std::string>{"128", "124", "173"}) == 3);
}

/////////////////////////////////////////////////////////////////////////////////////////////