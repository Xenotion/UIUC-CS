#include <iostream>
#include <stdexcept>

#include "dna_strand.hpp"
#include "node.hpp"

int main() {
  // two new DNA strands
  DNAstrand* strand = new DNAstrand();
  DNAstrand* to_splice_in = new DNAstrand();

  // pattern char array and original char array
  char* pattern = new char[3]{'T', 'A', '\0'};

  // print pattern array
  std::cout << "Pattern: " << std::endl;
  for (int i = 0; pattern[i] != '\0'; i++) {
    std::cout << pattern[i] << " ";
  }

  std::cout << std::endl << std::endl;

  char* orig = new char[6]{'C', 'T', 'A', 'T', 'A', '\0'};

  // create a new linked list based on orig array
  Node* yeet2 = new Node('C');
  strand->SetHead(yeet2);
  strand->SetTail(strand->Head());

  for (int i = 1; orig[i] != '\0'; i++) {
    Node* node = new Node(orig[i]);
    strand->Tail()->next = node;
    strand->SetTail(node);
  }

  // print the strand linked list
  std::cout << "Original linked list: " << std::endl;
  Node* current = strand->Head();
  while (current != nullptr) {
    std::cout << current->data << " ";
    current = current->next;
  }
  std::cout << std::endl << std::endl;

  // create a new linked list based on to_splice_in array
  char* to_splice_in_pattern = new char[4]{'T', 'G', 'A', '\0'};

  // create a new linked list based on to_splice_in_pattern array
  Node* yeet1 = new Node('T');
  to_splice_in->SetHead(yeet1);
  // delete yeet1;
  to_splice_in->SetTail(to_splice_in->Head());

  for (int i = 1; to_splice_in_pattern[i] != '\0'; i++) {
    Node* node = new Node(to_splice_in_pattern[i]);
    to_splice_in->Tail()->next = node;
    to_splice_in->SetTail(node);
    // delete node;
  }

  // print the to_splice_in linked list
  std::cout << "to_splice_in linked list: " << std::endl;
  current = to_splice_in->Head();
  while (current != nullptr) {
    std::cout << current->data << " ";
    current = current->next;
  }
  std::cout << std::endl << std::endl;

  // call the function you implemented in dna_strand.cc
  strand->SpliceIn(pattern, *to_splice_in);

  // prints the new linked list
  std::cout << "New linked list: " << std::endl;
  if (strand->Head() == nullptr) {
    throw std::invalid_argument("head is null");
  } else {
    Node* current2 = strand->Head();
    while (current2 != nullptr) {
      std::cout << current2->data << " ";
      current2 = current2->next;
    }
    std::cout << std::endl << std::endl;
  }

  // delete the linked lists
  delete strand;
  delete to_splice_in;
  delete[] pattern;
  delete[] orig;
  delete[] to_splice_in_pattern;

  return 0;
}