// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
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

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

void CopyBoard(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      solution[i][j] = student[i][j];
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Disk dropping", "[DropDiskToBoard]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty}
  };

  Board test;
  CopyBoard(test.board, solution);
  REQUIRE_THROWS_AS(DropDiskToBoard(test, DiskType::kPlayer1, 3), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(test, DiskType::kPlayer2, 3), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(test, DiskType::kPlayer1, 4), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(test, DiskType::kPlayer2, 4), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(test, DiskType::kPlayer1, -1), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(test, DiskType::kPlayer2, -3), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(test, DiskType::kPlayer1, 10), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(test, DiskType::kPlayer2, 8), std::runtime_error);
}

TEST_CASE("Search winner", "[SearchFroWinner]") {
  DiskType source[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };

  DiskType source2[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };

  DiskType source3[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
  };

  DiskType source4[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
  };

  DiskType source5[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
  };

  DiskType source6[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2}
  };

  Board test;
  Board test2;
  Board test3;
  Board test4;
  Board test5;
  Board test6;
  CopyBoard(test.board, source); // you would need to define this.
  CopyBoard(test2.board, source2);
  CopyBoard(test3.board, source3);
  CopyBoard(test4.board, source4);
  CopyBoard(test5.board, source5);
  CopyBoard(test6.board, source6);

  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kHorizontal));      
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kHorizontal));

  REQUIRE_FALSE(SearchForWinner(test2, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test2, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test2, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test2, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(test2, DiskType::kPlayer2, WinningDirection::kHorizontal));      
  REQUIRE_FALSE(SearchForWinner(test2, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(test2, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(test2, DiskType::kPlayer2, WinningDirection::kRightDiag));

  REQUIRE_FALSE(SearchForWinner(test3, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test3, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test3, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test3, DiskType::kPlayer1, WinningDirection::kHorizontal));  
  REQUIRE_FALSE(SearchForWinner(test3, DiskType::kPlayer2, WinningDirection::kHorizontal));    
  REQUIRE_FALSE(SearchForWinner(test3, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(test3, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(test3, DiskType::kPlayer1, WinningDirection::kLeftDiag));

  REQUIRE_FALSE(SearchForWinner(test4, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test4, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test4, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test4, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test4, DiskType::kPlayer1, WinningDirection::kHorizontal));  
  REQUIRE_FALSE(SearchForWinner(test4, DiskType::kPlayer2, WinningDirection::kHorizontal));    
  REQUIRE_FALSE(SearchForWinner(test4, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(test4, DiskType::kPlayer2, WinningDirection::kVertical));

  REQUIRE_FALSE(SearchForWinner(test5, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test5, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test5, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test5, DiskType::kPlayer1, WinningDirection::kHorizontal));  
  REQUIRE_FALSE(SearchForWinner(test5, DiskType::kPlayer2, WinningDirection::kHorizontal));    
  REQUIRE_FALSE(SearchForWinner(test5, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(test5, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(test5, DiskType::kPlayer1, WinningDirection::kLeftDiag));

  REQUIRE_FALSE(SearchForWinner(test6, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test6, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test6, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test6, DiskType::kPlayer1, WinningDirection::kHorizontal));  
  REQUIRE_FALSE(SearchForWinner(test6, DiskType::kPlayer2, WinningDirection::kHorizontal));    
  REQUIRE_FALSE(SearchForWinner(test6, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(test6, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(test6, DiskType::kPlayer2, WinningDirection::kRightDiag));
  
  REQUIRE(CheckForWinner(test, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(test, DiskType::kPlayer2));
  REQUIRE(CheckForWinner(test2, DiskType::kPlayer2));
  REQUIRE_FALSE(CheckForWinner(test2, DiskType::kPlayer1));
  REQUIRE(CheckForWinner(test3, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(test3, DiskType::kPlayer2));
  REQUIRE(CheckForWinner(test4, DiskType::kPlayer2));
  REQUIRE_FALSE(CheckForWinner(test4, DiskType::kPlayer1));
  REQUIRE(CheckForWinner(test5, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(test5, DiskType::kPlayer2));
  REQUIRE(CheckForWinner(test6, DiskType::kPlayer2));
  REQUIRE_FALSE(CheckForWinner(test6, DiskType::kPlayer1));
}

TEST_CASE("Board Location In Bounds", "[BoardLocationInBounds]") {
  REQUIRE_FALSE(BoardLocationInBounds(-1, -1));
  REQUIRE_FALSE(BoardLocationInBounds(0, 7));
  REQUIRE_FALSE(BoardLocationInBounds(1, 7));
  REQUIRE_FALSE(BoardLocationInBounds(2, 7));
  REQUIRE_FALSE(BoardLocationInBounds(3, 7));
  REQUIRE_FALSE(BoardLocationInBounds(4, 7));
  REQUIRE_FALSE(BoardLocationInBounds(5, 7));
  REQUIRE_FALSE(BoardLocationInBounds(6, 7));
  REQUIRE_FALSE(BoardLocationInBounds(7, 7));
  REQUIRE_FALSE(BoardLocationInBounds(7, 0));
  REQUIRE_FALSE(BoardLocationInBounds(7, 1));
  REQUIRE_FALSE(BoardLocationInBounds(7, 2));
  REQUIRE_FALSE(BoardLocationInBounds(7, 3));
  REQUIRE_FALSE(BoardLocationInBounds(7, 4));
  REQUIRE_FALSE(BoardLocationInBounds(7, 5));
  REQUIRE_FALSE(BoardLocationInBounds(7, 6));
  REQUIRE_FALSE(BoardLocationInBounds(7, 7));
  REQUIRE(BoardLocationInBounds(0, 0));
  REQUIRE(BoardLocationInBounds(1, 2));
  REQUIRE(BoardLocationInBounds(5, 6));
}
/////////////////////////////////////////////////////////////////////////////////////////////