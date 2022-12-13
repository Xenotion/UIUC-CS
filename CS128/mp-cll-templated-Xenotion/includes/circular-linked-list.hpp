#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void InsertHelpMid(Node<T>* new_node);
  void InsertHelpMid2(Node<T>* new_node);
  void Reverse();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  Node<T>* iter = source.head_;
  this->node_order_ = source.node_order_;
  if (iter == nullptr) {
    return;
  }
  do {
    InsertInOrder(iter->data);
    iter = iter->next;
  } while (iter != source.head_);
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(
    const CircularLinkedList<T>& source) {
  if (this == &source) {
    return *this;
  }
  Node<T>* iter = this->head_;
  this->~CircularLinkedList();
  this->node_order_ = source.node_order_;
  iter = source.head_;
  if (iter == nullptr) {
    return *this;
  }
  do {
    InsertInOrder(iter->data);
    iter = iter->next;
  } while (iter != source.head_);

  return *this;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  Node<T>* iter = this->head_;
  if (iter == nullptr) {
    return;
  }
  do {
    Node<T>* temp = iter;
    iter = iter->next;
    delete temp;
  } while (iter != this->head_);
  tail_ = nullptr;
  head_ = nullptr;
}

template <typename T>
void CircularLinkedList<T>::InsertHelpMid(Node<T>* new_node) {
  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
    head_->next = head_;
    tail_->next = head_;
    return;
  }
}

template <typename T>
void CircularLinkedList<T>::InsertHelpMid2(Node<T>* new_node) {
  tail_->next = new_node;
  tail_ = new_node;
  tail_->next = head_;
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  auto* new_node = new Node<T>(data);
  InsertHelpMid(new_node);
  Node<T>* iter = head_;
  do {
    if (node_order_ == Order::kASC) {
      if (iter->data > data) {
        new_node->next = iter;
        if (iter == head_) {
          head_ = new_node;
          tail_->next = head_;
        } else {
          Node<T>* prev = head_;
          while (prev->next != iter) {
            prev = prev->next;
          }
          prev->next = new_node;
        }
        return;
      }
    } else {
      if (iter->data < data) {
        new_node->next = iter;
        if (iter == head_) {
          head_ = new_node;
          tail_->next = head_;
        } else {
          Node<T>* prev = head_;
          while (prev->next != iter) {
            prev = prev->next;
          }
          prev->next = new_node;
        }
        return;
      }
    }
    iter = iter->next;
  } while (iter != head_);
  InsertHelpMid2(new_node);
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (head_ == nullptr) {
    if (node_order_ == Order::kASC) {
      node_order_ = Order::kDESC;
    } else {
      node_order_ = Order::kASC;
    }
  } else {
    Node<T>* prev = nullptr;
    Node<T>* curr = head_;
    Node<T>* next = nullptr;
    do {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    } while (curr != head_);
    head_->next = prev;
    tail_ = head_;
    head_ = prev;

    if (node_order_ == Order::kASC) {
      node_order_ = Order::kDESC;
    } else {
      node_order_ = Order::kASC;
    }
  }
}

#endif