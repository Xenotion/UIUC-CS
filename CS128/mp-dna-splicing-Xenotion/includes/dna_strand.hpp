#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();
  Node* BeforeLastPattern(Node* last_pattern, Node* current);
  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  void DeleteAndSetTail(Node* current, Node* last_pattern);
  // create a getter function for head_
  Node* Head() const { return head_; }
  // create a setter function for head_
  void SetHead(Node* head) { head_ = head; }
  // create a getter function for tail_
  Node* Tail() const { return tail_; }
  // create a setter function for tail_
  void SetTail(Node* tail) { tail_ = tail; }

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif