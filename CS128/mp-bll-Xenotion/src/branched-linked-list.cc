#include "branched-linked-list.hpp"

Node* BLL::AdvancedNode(Node* input) const {
  if (input == nullptr) { return nullptr; }
  if (input->next_bll_ != nullptr) { return input->next_bll_->head_; }
  return input->next_node_;
}

bool BLL::IsBLLAcyclic() const {
  if (head_ == nullptr) { return true; }
  Node* slow = head_;
  Node* fast = AdvancedNode(head_);

  while (fast != nullptr) {
    if (fast == slow) { return false; } 

    slow = AdvancedNode(slow);
    fast = AdvancedNode(fast);
    fast = AdvancedNode(fast);
  }
  return true;
}

BLL::BLL() { head_ = nullptr; }

BLL::BLL(const BLL& to_copy) {
  if (to_copy.head_ == nullptr) {
    head_ = nullptr;
    return;
  }
  head_ = new Node(to_copy.head_->data_);
  Node* curr = head_;
  Node* curr_copy = to_copy.head_;
  while (curr_copy->next_node_ != nullptr) {
    curr->next_node_ = new Node(curr_copy->next_node_->data_);
    curr = curr->next_node_;
    curr_copy = curr_copy->next_node_;
  }
  curr = head_;
  curr_copy = to_copy.head_;
  while (curr_copy->next_node_ != nullptr) {
    if (curr_copy->next_bll_ != nullptr) {
      curr->next_bll_ = new BLL(*curr_copy->next_bll_);
    }
    curr = curr->next_node_;
    curr_copy = curr_copy->next_node_;
  }
}

BLL::~BLL() {
  Clear();
}

void BLL::Clear() {
  Node* current = this->head_;
  while (current != nullptr) {
    if (current->next_bll_ != nullptr) {
      delete current->next_bll_;
      current->next_bll_ = nullptr;
    }
    Node* temp = current;
    current = current->next_node_;
    delete temp;
  }
}

Node* CopyNodeAndBLL(const Node* to_copy) {
  Node* new_node = new Node(to_copy->data_);
  if (to_copy->next_bll_ != nullptr) {
    new_node->next_bll_ = new BLL(*to_copy->next_bll_);
  }
  return new_node;
}

BLL& BLL::operator=(const BLL& rhs) {
  if (this == &rhs) {
    return *this;
  }
  Clear();
  if (rhs.head_ == nullptr) { 
    head_ = nullptr; 
    return *this;
  }
  head_ = CopyNodeAndBLL(rhs.head_);
  Node* current = head_;
  Node* rhs_current = rhs.head_;
  while (rhs_current->next_node_ != nullptr) {
    current->next_node_ = CopyNodeAndBLL(rhs_current->next_node_);
    current = current->next_node_;
    rhs_current = rhs_current->next_node_;
  }
  return *this;
}

Node* BLL::PushBack(char dat) {
  Node* new_node = new Node(dat);
  if (head_ == nullptr) {
    head_ = new_node;
  } else {
    Node* curr = head_;
    while (curr->next_node_ != nullptr) {
      curr = curr->next_node_;
    }
    curr->next_node_ = new_node;
  }
  return new_node;
}

char BLL::GetAt(size_t idx) const {
  if (head_ == nullptr) {
    throw std::out_of_range("Index out of range");
  }
  Node* current = head_;
  size_t count = 0;
  while (current != nullptr) {
    if (count == idx) {
      return current->data_;
    }
    if (current->next_bll_ != nullptr) {
      try {
        return current->next_bll_->GetAt(idx - count - 1);
      } catch (std::out_of_range& e) {
      }
    }
    current = current->next_node_;
    count++;
  }
  throw std::out_of_range("Index out of range");
}

void BLL::SetAt(size_t idx, char dat) {
  if (head_ == nullptr) {
    throw std::out_of_range("Index out of range");
  }
  Node* current = head_;
  size_t count = 0;
  while (current != nullptr) {
    if (count == idx) {
      current->data_ = dat;
      return;
    }
    if (current->next_bll_ != nullptr) {
      try {
        current->next_bll_->SetAt(idx - count - 1, dat);
        return;
      } catch (std::out_of_range& e) {
      }
    }
    current = current->next_node_;
    count++;
  }
  throw std::out_of_range("Index out of range");
}

void BLL::Join(size_t idx, BLL* list) {
  if (head_ == nullptr) {
    throw std::out_of_range("Index out of range");
  }
  Node* current = head_;
  size_t count = 0;
  while (current != nullptr) {
    if (count == idx) {
      if (current->next_bll_ != nullptr) {
        throw std::invalid_argument("next_bll at index is not null");
      }
      current->next_bll_ = list;
      break;
    }
    if (current->next_bll_ != nullptr) {
      try {
        current->next_bll_->Join(idx - count - 1, list);
        break;
      } catch (std::out_of_range& e) {
      }
    }
    current = current->next_node_;
    count++;
  }
  if (!IsBLLAcyclic()) {
    throw std::invalid_argument("BLL is acyclic");
  }
}

std::string BLL::ToString() const {
  std::string str;
  Node* curr = head_;
  while (curr != nullptr) {
    str += curr->data_;
    if (curr->next_bll_ != nullptr) {
      str += curr->next_bll_->ToString();
    }
    curr = curr->next_node_;
  }
  return str;
}

size_t BLL::Size() const {
  size_t size = 0;
  Node* curr = head_;
  while (curr != nullptr) {
    if (curr->next_bll_ != nullptr) {
      size += curr->next_bll_->Size();
    }
    size++;
    curr = curr->next_node_;
  }
  return size;
}
