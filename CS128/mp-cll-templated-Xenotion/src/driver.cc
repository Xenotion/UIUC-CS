#include <iostream>

#include "circular-linked-list.hpp"

int main() {
  // create a circular linked list using the class and insert some data
  CircularLinkedList<int> cll;
  cll.InsertInOrder(5);
  cll.InsertInOrder(3);
  cll.InsertInOrder(1);
  cll.InsertInOrder(4);
  cll.InsertInOrder(2);
  cll.InsertInOrder(2);

  // // print ciruclar linked list from head to tail
  std::cout << "Original" << std::endl;
  std::cout << cll << std::endl;
  // // reverse the circular linked list
  cll.Reverse();
  // // print circular linked list from head to tail
  cll.InsertInOrder(6);
  cll.InsertInOrder(2);
  std::cout << cll << std::endl;

  // // create another circular linked list using the copy constructor
  CircularLinkedList<int> cll2;
  cll2.InsertInOrder(4);
  cll2.InsertInOrder(1);

  CircularLinkedList<int> cll3;
  cll3.InsertInOrder(3);
  cll3.InsertInOrder(2);
  std::cout << "New linked list" << std::endl;
  std::cout << cll3 << std::endl;

  cll3 = cll2;
  std::cout << "Another linked list" << std::endl;
  std::cout << cll2 << std::endl;
  std::cout << "After copy consturctor (another to new)" << std::endl;
  std::cout << cll3 << std::endl;
  return 0;
}
