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

#include "branched-linked-list.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }

TEST_CASE("", "") {
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('i');

  REQUIRE(first->ToString() == "hi");
  REQUIRE(first->Size() == 2);
  delete first;
}

TEST_CASE("Acylic", "") {
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('i');

  REQUIRE(first->IsBLLAcyclic());
  delete first;
}

TEST_CASE("Acylic2", "") {
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('i');
  first->PushBack('j');
  
  REQUIRE(first->IsBLLAcyclic());
  delete first;
}

TEST_CASE("Acylic3", "") {
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('i');
  first->PushBack('j');
  first->PushBack('k');
  
  REQUIRE(first->IsBLLAcyclic());
  delete first;
}

TEST_CASE("Acylic4", "") {
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('i');
  first->PushBack('j');
  first->PushBack('k');
  first->PushBack('l');

  REQUIRE(first->IsBLLAcyclic());
  delete first;
}

TEST_CASE("Acylic5", "") {
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('i');
  first->PushBack('j');
  first->PushBack('k');
  first->PushBack('l');
  first->PushBack('m');

  REQUIRE(first->IsBLLAcyclic());
  delete first;
}

TEST_CASE("Acylic6", "") {
  BLL* first = new BLL();
  BLL* second = new BLL();
  first->PushBack('a');
  first->PushBack('b');
  second->PushBack('c');

  first->Join(1, second);
  REQUIRE(first->IsBLLAcyclic());
  delete first;
}
/////////////////////////////////////////////////////////////////////////////////////////////