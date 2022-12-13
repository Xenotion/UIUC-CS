#include "dna_strand.hpp"

#include <stdexcept>

DNAstrand::~DNAstrand() {
  Node* current = head_;
  while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;
  }
}

Node* FindLastPattern(Node* current, const char* pattern) {
  Node* last_pattern = nullptr;
  while (current != nullptr) {
    if (current->data == pattern[0]) {
      bool found = true;
      Node* current2 = current;
      for (int i = 0; pattern[i] != '\0'; i++) {
        if (current2 == nullptr) {
          found = false;
          break;
        }
        if (current2->data != pattern[i]) {
          found = false;
          break;
        }
        current2 = current2->next;
      }
      if (found) {
        last_pattern = current;
      }
    }
    current = current->next;
  }
  return last_pattern;
}

Node* DNAstrand::BeforeLastPattern(Node* last_pattern, Node* current) {
  Node* before_last_pattern = nullptr;
  if (last_pattern != nullptr) {
    current = head_; 
    while (current != nullptr) {
      if (current->next == last_pattern) {
        before_last_pattern = current;
        break;
      }
      current = current->next;
    }
  }
  return before_last_pattern;
}

Node* LastNodePattern(Node* last_pattern, int pattern_length) {
  Node* last_node_of_pattern = nullptr;
  if (last_pattern != nullptr) {
    last_node_of_pattern = last_pattern;
    for (int i = 0; i < pattern_length - 1; i++) {
      last_node_of_pattern = last_node_of_pattern->next;
    }
  }
  return last_node_of_pattern;
}

void DNAstrand::DeleteAndSetTail(Node* current, Node* last_pattern) {
  current = last_pattern;
  while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;
  }

  current = head_;
  while (current != nullptr) {
    if (current->next == nullptr) {
      tail_ = current;
      break;
    }
    current = current->next;
  }
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (pattern == nullptr) { throw std::invalid_argument("pattern is null"); }
  if (pattern[0] == '\0') { throw std::invalid_argument("pattern is empty"); }
  if (to_splice_in.head_ == nullptr) { return; }
  if (&to_splice_in == this) { return; }

  Node* current = head_;
  Node* last_pattern = FindLastPattern(current, pattern);

  if (last_pattern == nullptr) {
    throw std::invalid_argument("pattern not found");
  }

  Node* before_last_pattern = BeforeLastPattern(last_pattern, current);

  int pattern_length = 0;
  for (int i = 0; pattern[i] != '\0'; i++) {
    pattern_length++;
  }

  Node* last_node_of_pattern = LastNodePattern(last_pattern, pattern_length);
  
  if (before_last_pattern != nullptr) {
    before_last_pattern->next = to_splice_in.head_;
    to_splice_in.tail_->next = last_node_of_pattern->next;
    last_node_of_pattern->next = nullptr;
  } else {
    head_ = to_splice_in.head_;
    to_splice_in.tail_->next = last_node_of_pattern->next;
    last_node_of_pattern->next = nullptr;
  }

  DeleteAndSetTail(current, last_pattern);

  to_splice_in.head_ = nullptr;
  to_splice_in.tail_ = nullptr;
}