#include <iostream>

#include "branched-linked-list.hpp"

int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('i');

  std::cout << first->ToString() << std::endl;  // hi
  std::cout << first->Size() << std::endl;      // 2

  // /////////////////////////////////////

  BLL* second = new BLL();
  second->PushBack('i');
  second->PushBack('!');
  second->PushBack('@');

  std::cout << second->ToString() << std::endl;  // i!@
  std::cout << second->Size() << std::endl;      // 3

  // /////////////////////////////////////

  first->Join(1, second);

  std::cout << first->ToString() << std::endl;  // hii!@
  std::cout << first->Size() << std::endl;      // 5

  std::cout << second->ToString() << std::endl;  // i!@
  std::cout << second->Size() << std::endl;      // 3

  // get the char at the 3rd position in the linked list including the branches
  std::cout << "---------------------" << std::endl;
  std::cout << first->GetAt(4) << std::endl;
  std::cout << "---------------------" << std::endl;

  // set the char at the 3rd position in the linked list including the branches
  first->SetAt(4, '#');
  std::cout << "---------------------" << std::endl;
  std::cout << first->ToString() << std::endl;  // hii!#
  std::cout << "---------------------" << std::endl;
  // /////////////////////////////////////

  BLL* first_clone = new BLL();
  *first_clone = *first;

  std::cout << first_clone->ToString() << std::endl;  // hii!@
  std::cout << first_clone->Size() << std::endl;      // 5

  // create a new linked list and attach to second
  BLL* third = new BLL();
  third->PushBack('a');
  third->PushBack('b');
  third->PushBack('c');

  first->Join(3, third);

  std::cout << first->ToString() << std::endl;  // hiiabc!@
  std::cout << first->Size() << std::endl;      // 8

  // make a new linked list and make it cyclic to itself
  BLL* fourth = new BLL();
  fourth->PushBack('a');
  fourth->PushBack('b');
  fourth->PushBack('c');
  fourth->PushBack('d');

  // maka new linkned list and make it cyclic to the fourth
  BLL* fifth = new BLL();
  fifth->PushBack('1');
  fifth->PushBack('2');
  fifth->PushBack('3');
  fifth->PushBack('4');

  fourth->Join(3, fifth);
  // fifth->Join(3, fourth);

  // print the char at index 5
  std::cout << "---------------------" << std::endl;
  // std::cout << fourth->GetAtNode(0)->data_ << std::endl;
  // std::cout << fourth->GetAtNode(1)->data_ << std::endl;
  // std::cout << fourth->GetAtNode(2)->data_ << std::endl;
  // std::cout << fourth->GetAtNode(3)->data_ << std::endl;
  // std::cout << fourth->GetAtNode(4)->data_ << std::endl;
  // std::cout << fourth->GetAtNode(5)->data_ << std::endl;
  // std::cout << fourth->GetAtNode(6)->data_ << std::endl;
  // std::cout << fourth->GetAtNode(7)->data_ << std::endl;
  std::cout << "---------------------" << std::endl;
  // std::cout << fourth->GetAtSkip(0)->data_ << std::endl;
  // std::cout << fourth->GetAtSkip(1)->data_ << std::endl;
  // std::cout << fourth->GetAtSkip(2)->data_ << std::endl;
  // std::cout << fourth->GetAtSkip(3)->data_ << std::endl;
  // std::cout << fourth->GetAtSkip(4)->data_ << std::endl;
  // std::cout << fourth->GetAtSkip(5)->data_ << std::endl;
  // std::cout << fourth->GetAtSkip(6)->data_ << std::endl;
  // std::cout << fourth->GetAtSkip(7)->data_ << std::endl;
  std::cout << "---------------------" << std::endl;

  delete first;
  delete fourth;
  delete first_clone;

  return 0;
}

// #include <iostream>

// #include "branched-linked-list.hpp"

// int main() {
//   /* EXAMPLE INTERACTIONS WITH BLL */
//   BLL* first = new BLL();
//   first->PushBack('h');
//   first->PushBack('i');

//   std::cout << first->ToString() << std::endl; // hi
//   std::cout << first->Size() << std::endl; // 2

//   /////////////////////////////////////

//   BLL* second = new BLL();
//   second->PushBack('i');
//   second->PushBack('!');
//   second->PushBack('@');

//   std::cout << second->ToString() << std::endl; // i!@
//   std::cout << second->Size() << std::endl; // 3

//   /////////////////////////////////////

//   first->Join(1, second);

//   std::cout << first->ToString() << std::endl; // hii!@
//   std::cout << first->Size() << std::endl; // 5

//   std::cout << second->ToString() << std::endl; // i!@
//   std::cout << second->Size() << std::endl; // 3

//   /////////////////////////////////////

//   BLL* first_clone = new BLL();
//   *first_clone = *first;

//   std::cout << first_clone->ToString() << std::endl; // hii!@
//   std::cout << first_clone->Size() << std::endl; // 

//   delete first;
//   delete first_clone;
  
//   return 0;
// }